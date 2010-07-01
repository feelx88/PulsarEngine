#ifndef __constrainttoolkit__
#define __constrainttoolkit__

#include "IToolKit.h" // Base class: pulsar::IToolKit
#include "../Entities/Entity.h"

namespace pulsar
{

class ConstraintToolKit : public pulsar::IToolKit
{

public:

	/**
	 * @brief Standard constructor.
	 */
	ConstraintToolKit();

	/**
	 * @brief Standard destructor.
	 */
	virtual ~ConstraintToolKit();

	/**
	 * @brief Initialization method.
	 * @param initValue Not used.
	 */
	void init( Value initValue );

	/**
	 * @brief Add a point to point constraint between two Entitys.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 First Entity.
	 * @param pEntity2 Second Entity.
	 * @param pos1 Offset from the first Entity.
	 * @param pos2 Offset from the second Entity.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btPoint2PointConstraint *connectWithPoint2Point( unsigned int iID,
		Entity* pEntity1, Entity* pEntity2, Vector pos1, Vector pos2 );

	/**
	 * @brief Add a hinge constraint between two Entitys.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 First Entity.
	 * @param pEntity2 Second Entity.
	 * @param pos1 Offset from the first Entity.
	 * @param pos2 Offset from the second Entity.
	 * @param hingeAxis1 Axis of the hinge on first Entity.
	 * @param hingeAxis2 Axis of the hinge on second Entity.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btHingeConstraint *connectWithHinge( unsigned int iID, Entity* pEntity1, Entity* pEntity2,
		Vector pos1, Vector pos2, Vector hingeAxis1, Vector hingeAxis2 );

	/**
	 * @brief Add a slider constraint between two Entitys.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 First Entity.
	 * @param pEntity2 Second Entity.
	 * @param pos1 Offset from the first Entity.
	 * @param pos2 Offset from the second Entity.
	 * @param dir1 Axis of the slider on first Entity.
	 * @param dir2 Axis of the slider on second Entity.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btSliderConstraint *connectWithSlider( unsigned int iID, Entity *pEntity1, Entity *pEntity2,
		Vector pos1, Vector pos2, Vector dir1, Vector dir2 );

	//TODO: Change to create the constraint with all data set.
	btGeneric6DofConstraint *connectWith6DOF( unsigned int iID, Entity *pEntity1, Entity *pEntity2,
		Vector pos1, Vector pos2, Vector dir1, Vector dir2 );

	/**
	 * @brief Lock the specified Entity with a point 2 point constraint to the
	 * physics world.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 The Entity to be locked.
	 * @param pos1 Offset from the Entity.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btPoint2PointConstraint *lockWithPoint2Point( unsigned int iID,
		Entity *pEntity1, Vector pos1 );

	/**
	 * @brief Lock the specified Entity with a hinge constraint to the
	 * physics world.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 The Entity to be locked.
	 * @param pos1 Offset from the Entity.
	 * @param hingeAxis1 Axis of the hinge.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btHingeConstraint *lockWithHinge(unsigned int iID,  Entity *pEntity1, Vector pos1,
		Vector hingeAxis1 );

	/**
	 * @brief Lock the specified Entity with a slider constraint to the
	 * physics world.
	 * @param iID ID of the newly created constraint.
	 * @param pEntity1 The Entity to be locked.
	 * @param pos1 Offset from the Entity.
	 * @param dir1 Axis of the slider.
	 * @return A pointer to the created constraint or 0 if the creation was
	 * unsuccesful.
	 */
	btSliderConstraint *lockWithSlider( unsigned int iID, Entity *pEntity1, Vector pos1,
		Vector dir1 );

	//TODO: comment & implement
	void setLinearLimits( String sName, Vector low, Vector high );
	void setAngularLimits( String sName, Vector low, Vector high );

	void lockDOF( String sName, unsigned int iIndex );
	void unlockDOF( String sName, unsigned int iIndex );

	/**
	 * @brief Get the constraint with the given ID.
	 * @param iID ID of the Constraint.
	 * @return The constraint, or 0 if it does not exist.
	 */
	btTypedConstraint *getConstraint( unsigned int iID )
	{
		return m_mConstraints[iID];
	}

	void deleteConstraint( unsigned int iID )
	{
		m_mConstraints.erase( iID );
	}

protected:

	std::map<unsigned int, btTypedConstraint*> m_mConstraints;
};

}

#endif // __constrainttoolkit__
