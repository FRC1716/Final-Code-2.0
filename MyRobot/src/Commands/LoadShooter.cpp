// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "LoadShooter.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

LoadShooter::LoadShooter(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::mainSubsystem.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	SetInterruptible(true);
	finish = false;
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void LoadShooter::Initialize() {
	//Robot::mainSubsystem->loaderSol1.get()->Set(false);
	//Robot::mainSubsystem->loaderSol2.get()->Set(false);
	SmartDashboard::PutString("Shooter status: ", "init load");
	finish = false;
}

// Called repeatedly when this Command is scheduled to run
void LoadShooter::Execute() {
	//move loader to the back of the robot
	Robot::mainSubsystem->loaderSol1->Set(true);
	Robot::mainSubsystem->loaderSol2->Set(false);
	//wait for the loader to get to back
	Wait(2);
	//turn off loader and lock the latch
	Robot::mainSubsystem->loaderSol1->Set(false);
	Robot::mainSubsystem->loaderSol2->Set(false);
	Robot::mainSubsystem->latchSol1->Set(true);
	Robot::mainSubsystem->latchSol2->Set(false);
	//wait for guaranteed lock
	Wait(0.3);
	//move lower part of loader to the front of the robot
	Robot::mainSubsystem->loaderSol1->Set(false);
	Robot::mainSubsystem->loaderSol2->Set(true);
	//wait for lower loader to get to front
	Wait(1);
	//turn off loader
	Robot::mainSubsystem->loaderSol1->Set(false);
	Robot::mainSubsystem->loaderSol2->Set(false);

	finish = true;
}

// Make this return true when this Command no longer needs to run execute()
bool LoadShooter::IsFinished() {
	return finish;
}

// Called once after isFinished returns true
void LoadShooter::End() {
	//turn off solenoid components
	Robot::mainSubsystem->latchSol1->Set(false);
	Robot::mainSubsystem->latchSol2->Set(false);
	Robot::mainSubsystem->loaderSol1->Set(false);
	Robot::mainSubsystem->loaderSol2->Set(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LoadShooter::Interrupted() {
	End();
}
