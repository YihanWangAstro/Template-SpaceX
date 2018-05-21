////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Filename:integrator.h                                                                                               //
//Author:Yihan Wang                                                                                                   //
//                                                                                                                    //
//                                                                                                                    //
//Description:                                                                                                        //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SYMPLECTIC_8TH_INTEGRATOR_H
#define SYMPLECTIC_8TH_INTEGRATOR_H
/** @brief Eighth order symplectic integrator */
template <typename ParticSys>
class symplectic8th
{
    //////////////////////////////////Interface/////////////////////////////////////
public:
    /** @brief Order of the integrator*/
    static const int order{8};
    void integrate(ParticSys& particles, double stepLength);
};

/** @brief Interface to integrate particle system
 *
 *  This function integrate the particle system for one step with DKD leapfrog second order symplectic algorithm.
 *  @param particles  Particle system need to be integrated.
 *  @param stepLength Step size for integration.
 */
template <typename ParticSys>
void symplectic8th<ParticSys>::integrate(ParticSys& particles, double stepLength)
{
    particles.AdvancePos(0.5 * stepLength);
    particles.AdvanceVel(stepLength);
    particles.AdvancePos(0.5 * stepLength);
}
#endif
