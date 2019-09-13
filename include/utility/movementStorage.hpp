
#ifndef _MOVEMENT_STORAGE_HPP_
#define _MOVEMENT_STORAGE_HPP_

/**
 * This class is designed to store information for drive movements that need to be kept between movement iterations
 */
class MovementStorage
{
public:
  MovementStorage();

  double xDistance;
  double yDistance;
  double targetAngle;
  double error;
  double speed;
  double angleDifference;
  double deltaTime;
};

#endif