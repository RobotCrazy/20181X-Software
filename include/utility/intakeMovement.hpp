class IntakeMovement
{
private:
  int targetPosition;
  bool actionComplete = false;

public:
  IntakeMovement(int targetPos);

  bool readyToOperate();
};