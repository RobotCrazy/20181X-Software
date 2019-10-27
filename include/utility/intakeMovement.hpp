class IntakeMovement
{
private:
  int targetPosition;
  bool actionComplete = false;
  Prereq intakePrereq;

public:
  IntakeMovement(int targetPos);

  void setComplete();
  bool isComplete();
  void setIntakePrereq(Prereq p);
  bool readyToOperate();
};