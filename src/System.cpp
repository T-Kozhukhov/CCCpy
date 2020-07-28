#include "System.h"
#include "csv.h"
#include "cmdout.h"

System::System(){
    //ctor for python class
    simulationBegun = false; //set simReady and simBegin to false to start with
    simulationReady = false;    

    personList = std::vector<person>(0); //init the person list to avoid issues

    // title card
    cmdout::cmdWrite(true, "============================================");
    cmdout::cmdWrite(true, "|  Custom Crowds in C++ in Python (CCCpy)  |");
    cmdout::cmdWrite(true, "============================================");
    cmdout::cmdWrite(true, " "); //newline for spacing

    //set up default physParam parameters here
    ///TODO: set default physParam parameters here
    //step properties
    sysParam.stepSize = 0.01; // step size in seconds
    sysParam.stepMax = 100000; // how many steps the simulation should run for 
    //TODO: Is the above necessary to bind?

    //output information
    sysParam.outputSteps = 1000; // after how many steps should you output?
    //TODO: Is the above necessary to bind?
    sysParam.outDirPath = "./VTP/"; //path to output directory
    sysParam.outFileName = "VisualiserData"; //what file to store data into. .vtp extension should NOT be included
    sysParam.outFileType = "vtp"; //file tpye to save as (should be vtp, no dots)
    //TODO: Is the above necessary to bind?

    //particle properties
    sysParam.N = 300; //if randomly generating particles, this is how many to generate
    sysParam.meanR = 1; // mean radius
    sysParam.v_0 = 0.05; // active velocity parameter
    sysParam.sigmaR = 0.1; // standard deviation of the radius
    sysParam.sigmaV = 0; // standard deviation for when generating gaussian velocities
    sysParam.massRadiusRatio = 1; //ratio of particle mass to radius used for finding mass of particles

    //boundary consts
    sysParam.periodic = true; // is the boundary periodic or no?
    sysParam.L_x = 40;
    sysParam.L_y = 40;
    sysParam.overlapRatio = 0; //overlap ratio if the boundary is not periodic

    //csv information
    sysParam.loadParticles = false; // whether to load particles or not
    sysParam.pathToParticles = ""; //full file path to csv containing particle information
    sysParam.pathToLoadingCSV = "./"; //file path to where the physParam, init particle state, and single file is dumped
    sysParam.particleDumpSteps = 0; //after how many steps to dump particle data. 0 for no dumping
    sysParam.pathToParticleData = "./ParticleData/"; //file path to the directory where particle data should be stored
    sysParam.dumpSingleParticle = false; //whether to dump a single particle or not

    //force bools - Do we want to consider the following forces in our sim, yay or nay?
    sysParam.enableHarmonicInterForce = false;
    sysParam.enableHertzianInterForce = false;
    sysParam.enableActiveForce = false;
    sysParam.enableGroundFrictionForce = false;
    sysParam.enablePersonFrictionForce = false;
    sysParam.enableRandNoisyForce = false;

    //force parameters
    sysParam.zetaActive = 1; // friction parameter for active propulsion
    sysParam.zetaGround = 1; // friction parameter against the ground
    sysParam.zetaPerson = 1; // friction parameter against other people
    sysParam.kHarmonic = 1; // harmonic spring const between particles
    sysParam.kHertzian = 1; // hertzian const between particles
    sysParam.sigmaForceX = 0.2; // standard deviation for the force resulted from noise in the x axis
    sysParam.sigmaForceY = 0.2; // standard deviation for the force resulted from noise in the y axis

    //torque bools - Do we want to conside the following torques in oru sim, yay or nay?
    sysParam.enablePolarAlignmentTorque = false;
    sysParam.enableVelocityAlignmentTorque = false;
    sysParam.enableAngularFrictionTorque = false;
    sysParam.enablePairDissipationTorque = false;
    sysParam.enableRandNoisyTorque = false;

    //torque parameters
    sysParam.xiAngular = 1; //angular friction coeff
    sysParam.xiPair = 1; //pair dissipation coeff
    sysParam.zetaPolar = 1; //polar alignment coeff
    sysParam.zetaVelocity = 0.1; //velocity alignment coeff
    sysParam.sigmaTorque = 0.2; //SD for the torque resulted from noise

    //debug parameters
    sysParam.debugType = physParam::None; //see physparam header for full list of debug states
}

System::System(physParam param)
{
    ///TODO: not needed in python binaries, remove later
    //ctor
    sysParam = param;
    simulationBegun = false;
    personList = std::vector<person>(0);

    person::setMassRadiusRatio(sysParam.massRadiusRatio); //set the mass-radius ratio of particles now before any are generated

    //handling boundary stuff here
    bManager = boundaryManager(sysParam.periodic, sysParam.L_x, sysParam.L_y);

    //preparing fManager and tManager by getting the necessary parameters from sysParam
    fManager = force(&bManager, sysParam.zetaActive, sysParam.zetaGround, sysParam.zetaPerson,
        sysParam.v_0, sysParam.kHarmonic, sysParam.kHertzian);
    tManager = planarTorque(sysParam.xiAngular, sysParam.xiPair, sysParam.zetaPolar,
        sysParam.zetaVelocity);

    //setup of output manager
    vtpDumper = output(sysParam.outFileName, sysParam.outDirPath, sysParam.outFileType, &personList);
}

System::~System()
{
    //dtor
    //kill off all pointers that need to exist for the entire system duration
    for(unsigned int i = 0; i< personList.size(); i++){
        personList.at(i).killPointers(); //kill off person pointers
    }
}

void System::setVerbose(){
    cmdout::setVerbose();
}

void System::setParamDumpSingleFile(std::string pathToParticleData){
    if(checkParamEditable()){
        sysParam.dumpSingleParticle=true;
        sysParam.pathToParticleData = pathToParticleData; //set the flag for dumping particle data and the corresponding path

        csv::setupSingleFile(sysParam.pathToParticleData);
    }
}

void System::writeReadablePhysParam(){
    //spaghetti code dump, writes a readable version of the physparam
    cmdout::cmdWrite(true, "Dumping readable form of currently written parameters. [B] indicates a boolean variable.")
    cmdout::cmdWrite(true, "Step size: "+std::to_string(sysParam.stepSize));
    cmdout::cmdWrite(true, "Maximum number of steps: "+std::to_string(sysParam.stepMax));
    cmdout::cmdWrite(true, "Dump .vtp files every n steps. n: "+std::to_string(sysParam.outputSteps));
    cmdout::cmdWrite(true, "The directory to store .vtp files in: "+sysParam.outDirPath);
    cmdout::cmdWrite(true, "Prefix to the timestamp for .vtp files: "+sysParam.outFileName);
    cmdout::cmdWrite(true, "Output file type (should typically be vtp): "+sysParam.outFileType);
    cmdout::cmdWrite(true, "If randomly generating N particles (or debug type 0), how many particles to generate: "+std::to_string(sysParam.N));
    cmdout::cmdWrite(true, "Mean radius of particles: "+std::to_string(sysParam.meanR));
    cmdout::cmdWrite(true, "Standard deviation of radius of particles: "+std::to_string(sysParam.sigmaR));
    cmdout::cmdWrite(true, "Standard deviation of initial velocity of particles: "+std::to_string(sysParam.sigmaV));
    cmdout::cmdWrite(true, "[B] Does the system have periodic BCs: "+std::to_string(sysParam.periodic));
    cmdout::cmdWrite(true, "Size of the system box in the x direction: "+std::to_string(sysParam.L_x));
    cmdout::cmdWrite(true, "Size of the system box in the y direction: "+std::to_string(sysParam.L_y));
    cmdout::cmdWrite(true, "If generating 'boundary particles', the 'overlap ratio' between generated boundary particles: "+std::to_string(sysParam.overlapRatio));
    cmdout::cmdWrite(true, "[B] Whether to load particle ICs from a file: "+std::to_string(sysParam.loadParticles));
    cmdout::cmdWrite(true, "The full file path leading to the .csv file containing particle ICs: "+sysParam.pathToParticles);
    cmdout::cmdWrite(true, "File path where CSVs for loading will be stored: "+sysParam.pathToLoadingCSV);
    cmdout::cmdWrite(true, "Dump particle information every n steps (0 means no dumps). n: "+std::to_string(sysParam.particleDumpSteps));
    cmdout::cmdWrite(true, "File path where particle information will be stored: "+sysParam.pathToParticleData);
    cmdout::cmdWrite(true, "[B] Are harmonic interactional forces enabled: "+std::to_string(sysParam.enableHarmonicInterForce));
    cmdout::cmdWrite(true, "[B] Are hertzian interactional forces enabled: "+std::to_string(sysParam.enableHertzianInterForce));
    cmdout::cmdWrite(true, "[B] Are particle active forces enabled: "+std::to_string(sysParam.enableActiveForce));
    cmdout::cmdWrite(true, "[B] Are particle ground friction forces enabled: "+std::to_string(sysParam.enableGroundFrictionForce));
    cmdout::cmdWrite(true, "[B] Are particle person friction forces enabled: "+std::to_string(sysParam.enablePersonFrictionForce));
    cmdout::cmdWrite(true, "[B] Are particle random noisy forces enabled: "+std::to_string(sysParam.enableRandNoisyForce));
    cmdout::cmdWrite(true, "Friction parameter included only in the active force: "+std::to_string(sysParam.zetaActive));
    cmdout::cmdWrite(true, "cmdout::cmdWrite(true, Friction parameter against the ground, included only in the ground friction force: "+std::to_string(sysParam.zetaGround));
    cmdout::cmdWrite(true, "Friction parameter against other people, used only in person friction force: "+std::to_string(sysParam.zetaPerson));
    cmdout::cmdWrite(true, "V_0 parameter. Affects both initial velocities and the active force: "+std::to_string(sysParam.v_0));
    cmdout::cmdWrite(true, "Spring constant used in harmonic interactional forces: "+std::to_string(sysParam.kHarmonic));
    cmdout::cmdWrite(true, "Spring constant used in hertzian interactional forces: "+std::to_string(sysParam.kHertzian));
    cmdout::cmdWrite(true, "Standard deviation in the x direction for random noisy forces: "+std::to_string(sysParam.sigmaForceX));
    cmdout::cmdWrite(true, "Standard deviation in the y direction for random noisy forces: "+std::to_string(sysParam.sigmaForceY));
    cmdout::cmdWrite(true, "[B] Are polar alignment torques enabled: "+std::to_string(sysParam.enablePolarAlignmentTorque));
    cmdout::cmdWrite(true, "[B] Are velocity alignment torques enabled: "+std::to_string(sysParam.enableVelocityAlignmentTorque));
    cmdout::cmdWrite(true, "[B] Are angular friction torques enabled: "+std::to_string(sysParam.enableAngularFrictionTorque));
    cmdout::cmdWrite(true, "[B] Are pair dissipation torques enabled: "+std::to_string(sysParam.enablePairDissipationTorque));
    cmdout::cmdWrite(true, "[B] Are random noisy torques enabled: "+std::to_string(sysParam.enableRandNoisyTorque));
    cmdout::cmdWrite(true, "Friction parameter for angular friction torques: "+std::to_string(sysParam.xiAngular));
    cmdout::cmdWrite(true, "Friction parameter for pair dissipation torques: "+std::to_string(sysParam.xiPair));
    cmdout::cmdWrite(true, "Coefficient of polar alignment torques: "+std::to_string(sysParam.zetaPolar));
    cmdout::cmdWrite(true, "Coefficient of velocity alignment torques: "+std::to_string(sysParam.zetaVelocity));
    cmdout::cmdWrite(true, "Standard deviation for random noisy torques: "+std::to_string(sysParam.sigmaTorque));
    cmdout::cmdWrite(true, "Debug override. IF NOT 0, uses hardcoded overrides for initial conditions. See docs for more details: "+std::to_string(sysParam.debugType));
    cmdout::cmdWrite(true, "[B] If dumping particle data, do we dump only a single particle to a single file: "+std::to_string(sysParam.dumpSingleParticle));
    cmdout::cmdWrite(true, "Ratio of mass to radius^2, used for calculating mass of particles: "+std::to_string(sysParam.massRadiusRatio);
}

void System::prepareSimulation(){
    // prepares the simulation as the old CCC system class constructor used to do
    person::setMassRadiusRatio(sysParam.massRadiusRatio); //set the mass-radius ratio of particles now before any are generated

    //handling boundary stuff here
    bManager = boundaryManager(sysParam.periodic, sysParam.L_x, sysParam.L_y);

    //preparing fManager and tManager by getting the necessary parameters from sysParam
    fManager = force(&bManager, sysParam.zetaActive, sysParam.zetaGround, sysParam.zetaPerson,
        sysParam.v_0, sysParam.kHarmonic, sysParam.kHertzian);
    tManager = planarTorque(sysParam.xiAngular, sysParam.xiPair, sysParam.zetaPolar,
        sysParam.zetaVelocity);

    //setup of output manager
    vtpDumper = output(sysParam.outFileName, sysParam.outDirPath, sysParam.outFileType, &personList);

    initParticles(); //init particles at this point

    //perform exporting
    csv::exportPList(personList, sysParam.pathToLoadingCSV+"initPartData.csv", sysParam.meanR); //exports the IC data for potential later usage
    csv::exportPhysParam(sysParam, sysParam.pathToLoadingCSV); //export the sysParam we have at this point for later usage

    simulationReady = true; //at this point it's safe to run the simulation

    cmdout::cmdWrite(false, "Simulation has been prepared. PhysParams are no longer editable.");
}

void System::runSimulation(){
    /// TODO: function is not needed in python binaries, remove later
    cmdout::cmdWrite(false, "Preparing simulation");

    initParticles(); //initialise particles
    csv::exportPList(personList, sysParam.pathToLoadingCSV+"initPartData.csv", sysParam.meanR); //exports the IC data for potential later usage

    cmdout::cmdWrite(false, "Executing simulation");
    simulationBegun = true; //set the simulation as begun to catch errors

    for(int t = 0; t<sysParam.stepMax; t++){ // perform appropriate number of steps
        step(t);
    }

    cmdout::cmdWrite(true, "Simulation completed. Output at: " + vtpDumper.getPathInfo());
}

void System::initParticles(){
    if(sysParam.debugType!=physParam::None){ //If we are in a debug state, then override accordingly
        generateDebugParticles();
    } else if(sysParam.loadParticles){ //otherwise, if we are to load particles
        std::vector<person> tempList = csv::importPList(sysParam.pathToParticles); //load particles into a temp vector
        mergePList(tempList); // merge the temporary list into the main lsit
    } else { //if no loading has been specified, just generate random particles within the domain
        std::vector<person> tempList; //create a temp list

        for(int i = 0; i<sysParam.N; i++){ //create N random particles as follows:
            if(bManager.getPeriodic()){ //if we're using periodic boundary conditions, then...
                tempList.push_back(person::getRandPerson(false, i, sysParam.meanR, sysParam.sigmaR, sysParam.v_0, sysParam.sigmaV, &randGen, &bManager)); //make a normal person
            }else{ //if we're not using a periodic boundary, thus using a fixed "particle wall" around the domain...
                //in this case, we need to stop particle deployments directly on the wall, so...
                mathVector pos = bManager.getRandPos(&randGen, sysParam.meanR*2); //get a position within the domain that is further than 2 average radius' from the boundary
                person tempPerson = person::getRandPerson(false, i, sysParam.meanR, sysParam.sigmaR, sysParam.v_0, sysParam.sigmaV, &randGen, pos);
                tempList.push_back(tempPerson); //create an otherwise random particle at that position
            }
        }

        mergePList(tempList);// merge the temp list into the main pList
    }
}

void System::step(int t){
    //We do all dumping before we do maths.
    //check to see if we should output on this step or not
    if (t%sysParam.outputSteps == 0){ ///TODO: remove
        vtpDumper.dump(t);
    }

    //check to see if we should dump particle data
    if(sysParam.particleDumpSteps!=0){ //if we're supposed to dump particle data....
        if(t%sysParam.particleDumpSteps == 0){ //and it's the correct step to dump particle data
            if(sysParam.dumpSingleParticle){
                csv::dumpSingleParticleData(personList, t*sysParam.stepSize, 0); //dump a single particle if specified
            } else { //otherwise dump all particles
                //make file path
                std::stringstream ss;
                ss << sysParam.pathToParticleData << "ParticleData" << t <<".csv";

                csv::dumpParticleData(personList, ss.str(), t*sysParam.stepSize); //dump all particles to file path
            }
        }
    }

    //Now do mathematics related stuff
    //first, check to see if neighbour lists need to be updated
    if(neighbourList::checkUpdate(&personList, &bManager)){
        neighbourList::updateLists(&personList, &bManager); //update the neighbour lists if necessary
    }

    //loop through all non-glued particles...
    for(unsigned int i = 0; i < personList.size(); i++){
        if(!personList[i].getGlued()){
            calculateForcesTorques(i); //calculate the forces acting on each non-glued particle
        }
    }

    // perform dynamics for all non-glued particles particles
    for(unsigned int i = 0; i<personList.size(); i++){
        if(!personList[i].getGlued()) {
            personList[i].update(sysParam.stepSize, &bManager); //if not glued, update each particle
        }
    }
}

void System::mergePList(std::vector<person> newList){
    mergePList(&personList, newList);
}

void System::mergePList(std::vector<person> *parentList, std::vector<person> newList){
    if(simulationBegun){ //if the simulation has already begun, throw some output and escape
        cmdout::cmdWrite(true, "Error: The program attempted to merge the pList after the simulation had already started.");
        cmdout::cmdWrite(true, "Do all merging before starting the simulation 'step loop' begins. Merging was skipped.");
        return;
    }

    //otherwise, if the simulation hasn't begun move the list
    for(unsigned int i =0; i<newList.size();i++){
        parentList->push_back(newList.at(i));
    }

    //now loop through pList and update IDs for particles
    for(unsigned int i = 0; i < parentList->size(); i++){
        parentList->at(i).setID(i);
    }

    neighbourList::updateLists(&personList, &bManager); //update the neighbour lists to make the program ready for use
}

bool System::checkParamEditable(){
    if(simulationReady){ //if the sim is ready to begin, then the sysParam should not be further edited
        cmdout::cmdWrite(true, "Simulation has been prepared. PhysParams are not further editable.");
        return false;
    } else if (simulationBegun){
        cmdout::cmdWrite(true, "Simulation has begun. PhysParams are not further editable.");
        return false;
    } else {
        return true;
    }
}

void System::calculateForcesTorques(int i){ //calculate the force and torques acting on particle i here
    //get p_i for readability here
    person *p_i = &personList[i];

    //obtain the neighbourlist for this particle
    std::vector<int> nList = p_i->getCurrNList();

    p_i->setForce(mathVector()); //reset force on particle to a 0 vector
    p_i->setTorque(0); //reset torque on particle to 0
    p_i->setNoisyForce(mathVector()); //reset noise force
    p_i->setNoisyTorque(0); //reset noise torque

    for(unsigned int j = 0; j<nList.size(); j++){ //for each of the neighbours...
        if(nList[j]!=i){ //only run the following if the particle isn't using itself as a neighbour
            //for readability, get p_j
            person *p_j = &personList[nList[j]]; // p_j is actually the person at the j'th entry in the nList, not the j'th entry in the main pList!!

            //paired forces, only calculate and add if sysParam specified to do so
            if(sysParam.enableHarmonicInterForce) { p_i->addForce(fManager.computeHarmonicInterForce(p_i, p_j)); }
            if(sysParam.enableHertzianInterForce) { p_i->addForce(fManager.computeHertzianInterForce(p_i, p_j)); }
            if(sysParam.enablePersonFrictionForce) { p_i->addForce(fManager.computePersonFrictionForce(p_i, p_j)); }

            //paired torques, only calculate and add if sysParam specified to do so
            if(sysParam.enablePolarAlignmentTorque) { p_i->addTorque(tManager.computePolarAlignmentTorque(p_i, p_j)); }
            if(sysParam.enablePairDissipationTorque) { p_i->addTorque(tManager.computePairDissipationTorque(p_i, p_j)); }
        }
    }

    //single forces, only calculate and add if sysParam specified to do so
    if(sysParam.enableActiveForce) { p_i->addForce(fManager.computeActiveForce(p_i)); }
    if(sysParam.enableGroundFrictionForce) { p_i->addForce(fManager.computeGroundFrictionForce(p_i)); }
    if(sysParam.enableRandNoisyForce) { p_i->setNoisyForce(fManager.randNoisyForce(&randGen, sysParam.sigmaForceX, sysParam.sigmaForceY)); }

    //single torques, only calculate and add if sysParam specified to do so
    if(sysParam.enableVelocityAlignmentTorque) { p_i->addTorque(tManager.computeVelocityAlignmentTorque(p_i)); }
    if(sysParam.enableAngularFrictionTorque) { p_i->addTorque(tManager.computeAngularFrictionTorque(p_i)); }
    if(sysParam.enableRandNoisyTorque) { p_i->setNoisyTorque(tManager.randNoisyTorque(&randGen, sysParam.sigmaTorque)); }
}

void System::generateDebugParticles(){
    //This subroutine is used to hardcode particles to debug the code
    std::vector<person> debugParticles; //this is the list we're handling in this subroutine

    if(sysParam.debugType==physParam::SingleAlongXAxis){
        //SingleAlongXAxis = Deploy a single particle going at const velocity along the x axis
        mathVector pos = bManager.getScaledPeriodicPos(0.5, 0.5);
        mathVector vel = mathVector(sysParam.v_0, 0);
        double polAngle = 0; //makes the particle go in the +ve x direction
        debugParticles.push_back(person(false, 0, sysParam.meanR, sysParam.meanR, pos, vel, polAngle));
    }
    else if (sysParam.debugType==physParam::SingleAlongRandAxis){
        //SingleAlongRandAxis = Deploy a single particle going at const velocity along a random axis
        mathVector pos = bManager.getScaledPeriodicPos(0.5, 0.5); //puts the particle directly in the center
        double polAngle = randGen.getUniformDouble(0, 6.28318530); //generate a random number between 0 and 2*PI
        mathVector vel = mathVector::getPolarVector(sysParam.v_0, polAngle); //generate a random velocity vector by using the previous magnitude and angle
        debugParticles.push_back(person(false, 0, sysParam.meanR, sysParam.meanR, pos, vel, polAngle));
    }
    else if (sysParam.debugType==physParam::DoubleCenterCollision){
        //DoubleCenterCollision = Deploy two identical particles, each travelling towards each other parallel to the x axis aiming for a collision
        //particle 1, going in +ve x direction
        mathVector pos1 = bManager.getScaledPeriodicPos(0.25, 0.5);
        mathVector vel1 = mathVector(sysParam.v_0, 0);
        double polAngle1 = 0;
        debugParticles.push_back(person(false, 0, sysParam.meanR, sysParam.meanR, pos1, vel1, polAngle1));

        //particle 2, going in -ve x direction
        mathVector pos2 = bManager.getScaledPeriodicPos(0.75, 0.5);
        mathVector vel2 = mathVector(-sysParam.v_0, 0);
        double polAngle2 =  3.141592;
        debugParticles.push_back(person(false, 1, sysParam.meanR, sysParam.meanR, pos2, vel2, polAngle2));
    }
    else if (sysParam.debugType==physParam::DoubleEdgeCollision){
        //DoubleEdgeCollision = Deploy two identical particles, each travelling towards each other such they collide on the boundary
        //particle 1, going in -ve x direction
        mathVector pos1 = bManager.getScaledPeriodicPos(0.25, 0.5);
        mathVector vel1 = mathVector(-sysParam.v_0, 0);
        double polAngle1 = 3.141592;
        debugParticles.push_back(person(false, 0, sysParam.meanR, sysParam.meanR, pos1, vel1, polAngle1));

        //particle 2, going in +ve x direction
        mathVector pos2 = bManager.getScaledPeriodicPos(0.75, 0.5);
        mathVector vel2 = mathVector(sysParam.v_0, 0);
        double polAngle2 =  0;
        debugParticles.push_back(person(false, 1, sysParam.meanR, sysParam.meanR, pos2, vel2, polAngle2));
    }
    else if (sysParam.debugType==physParam::Corridor){
        //Corridor = Deploy N particles within a horizontal corridor of length L_x. Intended to be used with periodic BCs
        const double widthScale = 0.4; //how much of L_y, as a scalar, should be used as the width of the corridor

        //get position related information
        double corridorMid = bManager.getScaledPos(0.5,0.5).getY(); //middle of corridor
        double dY = bManager.getScaledPos(0,0.5*widthScale).getY(); //difference between corridor walls and midpoint
        double corridorLength = bManager.getScaledPos(1, 0).getX(); //getting the length of the corridor
        double corridorTop = corridorMid+dY;
        double corridorBot = corridorMid-dY;

        //generate the "walls"
        std::vector<person> topWall = bManager.placeHorizontalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, corridorTop, 0, corridorLength);
        std::vector<person> botWall = bManager.placeHorizontalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, corridorBot, 0, corridorLength);

        //merge the walls into our debugParticles list
        mergePList(&debugParticles, topWall);
        mergePList(&debugParticles, botWall);

        //now generate N particles within that domain, but away from the "walls"
        const double wallDist = sysParam.meanR*2; //how far away from the walls you have to be
        for(int i = 0; i<sysParam.N; i++){ //create N random particles as follows:
            mathVector pos = bManager.getRandPos(&randGen, 0, corridorLength, corridorBot+wallDist, corridorTop-wallDist); //generate a random position within the corridor but away from walls
            person tempPerson = person::getRandPerson(false, i, sysParam.meanR, sysParam.sigmaR, sysParam.v_0, sysParam.sigmaV, &randGen, pos);
            debugParticles.push_back(tempPerson); //create an otherwise random particle at that position
        }
    }
    else if (sysParam.debugType==physParam::Box){
        //Box = Deploy N particles within a square box along the boundaries.
        //get box height and length
        double height = bManager.getScaledPos(1,1).getY();
        double width = bManager.getScaledPos(1,1).getX();

        //generate the walls
        std::vector<person> topWall = bManager.placeHorizontalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, height, 0, width);
        std::vector<person> botWall = bManager.placeHorizontalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, 0, 0, width);
        std::vector<person> leftWall = bManager.placeVerticalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, 0, 0, height);
        std::vector<person> rightWall = bManager.placeVerticalBoundaryParticles(sysParam.meanR, sysParam.overlapRatio, width, 0, height);

        //merge the walls into the debug list
        mergePList(&debugParticles, topWall);
        mergePList(&debugParticles, botWall);
        mergePList(&debugParticles, leftWall);
        mergePList(&debugParticles, rightWall);

        //now generate N particles within that domain but away from the "walls"
        const double wallDist = sysParam.meanR*2; ///how far away from the walls you have to be, change as appopriate
        for(int i = 0; i<sysParam.N; i++){ //create N random particles as follows:
            mathVector pos = bManager.getRandPos(&randGen, wallDist, width-wallDist, wallDist, height-wallDist); //generate a random position within the box but away from walls
            person tempPerson = person::getRandPerson(false, i, sysParam.meanR, sysParam.sigmaR, sysParam.v_0, sysParam.sigmaV, &randGen, pos);
            debugParticles.push_back(tempPerson); //create an otherwise random particle at that position
        }
    }
    else if (sysParam.debugType==physParam::Cluster){
        //Cluster = Delpoy 4 particles close to each other within a cluster, and a singular particle below them outside the cluster, all going in the same direction

        //get a vector pointing to center and a particle average radius
        mathVector center = bManager.getScaledPos(0.5,0.5);
        double radius = sysParam.meanR;

        //generate positions based on the center and radius
        //cluster positions are 3 radii above the center in a square block s.t. they touch each other perfectly
        mathVector pos1 = mathVector(center.getX(), center.getY()+3*radius);
        mathVector pos2 = mathVector(center.getX()+2*radius, center.getY()+3*radius);
        mathVector pos3 = mathVector(center.getX()+2*radius, center.getY()+5*radius);
        mathVector pos4 = mathVector(center.getX(), center.getY()+5*radius);
        //position for singleton particle
        mathVector pos5 = mathVector(center.getX(), center.getY()-3*radius);

        //now create the 5 particles with appropriate position, all going at speed v_0 in the +ve direction
        mathVector vel = mathVector(sysParam.v_0, 0); //make a velocity vector as appropriate
        debugParticles.push_back(person(false, 0, radius, radius, pos1, vel, 0));
        debugParticles.push_back(person(false, 1, radius, radius, pos2, vel, 0));
        debugParticles.push_back(person(false, 2, radius, radius, pos3, vel, 0));
        debugParticles.push_back(person(false, 3, radius, radius, pos4, vel, 0));
        debugParticles.push_back(person(false, 4, radius, radius, pos5, vel, 0));
    }

    mergePList(debugParticles); //merge debug particles into main pList
}
