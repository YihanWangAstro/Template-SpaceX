//
// Created by root on 10/7/19.
//
#include "dev-tools.hpp"

#ifndef SPACEHUB_ACCELERATIONS_H
#define SPACEHUB_ACCELERATIONS_H
namespace space {
/*---------------------------------------------------------------------------*\
    Class Accelerations Declaration
\*---------------------------------------------------------------------------*/
    template<typename Interactions, typename Coord>
    class Accelerations  {
    public:
        // Constructors
        Accelerations() = default;

        explicit Accelerations(size_t size) : acc_{size}, newtonian_acc_{size} {
            if constexpr (Interactions::ext_vel_indep) {
                ext_vel_indep_acc_.resize(size);
                tot_vel_indep_acc_.resize(size);
            }
            if constexpr (Interactions::ext_vel_dep) {
                ext_vel_dep_acc_.resize(size);
            }
        };

        Accelerations(Accelerations const &) = default;

        Accelerations(Accelerations &&) noexcept = default;

        Accelerations &operator=(Accelerations const &) = default;

        Accelerations &operator=(Accelerations &&) noexcept = default;

        //Public methods
        SPACEHUB_STD_ACCESSOR(auto, acc, acc_);

        SPACEHUB_STD_ACCESSOR(auto, newtonain_acc, newtonian_acc_);

        SPACEHUB_STD_ACCESSOR(auto, tot_vel_indep_acc, tot_vel_indep_acc_);

        SPACEHUB_STD_ACCESSOR(auto, ext_vel_indep_acc, ext_vel_indep_acc_);

        SPACEHUB_STD_ACCESSOR(auto, ext_vel_dep_acc, ext_vel_dep_acc_);

    private:
        Coord acc_;

        Coord newtonian_acc_;

        std::conditional_t<Interactions::ext_vel_indep, Coord, Empty> tot_vel_indep_acc_;

        std::conditional_t<Interactions::ext_vel_indep, Coord, Empty> ext_vel_indep_acc_;

        std::conditional_t<Interactions::ext_vel_dep, Coord, Empty> ext_vel_dep_acc_;
    };

/*---------------------------------------------------------------------------*\
    Class Accelerations Implementation
\*---------------------------------------------------------------------------*/
}
#endif //SPACEHUB_ACCELERATIONS_H
