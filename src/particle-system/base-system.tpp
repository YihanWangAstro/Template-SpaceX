
#ifndef GENPARTICLESYSTEM_H
#define GENPARTICLESYSTEM_H

#include "../core-computation.h"
#include "../dev-tools.h"
#include "../particle-system.h"


namespace SpaceH {

    template<typename Particles, typename Interactions>
    class SimpleSystem : public ParticleSystem<SimpleSystem<Particles, Interactions>> {
    public:
        SPACEHUB_USING_TYPE_SYSTEM_OF(Particles);

        SPACEHUB_STD_ACCESSOR(impl_mass, ptc_.mass());

        SPACEHUB_STD_ACCESSOR(impl_idn, ptc_.idn());

        SPACEHUB_STD_ACCESSOR(impl_pos, ptc_.pos());

        SPACEHUB_STD_ACCESSOR(impl_vel, ptc_.vel());

        SPACEHUB_STD_ACCESSOR(impl_time, ptc_.time());

        SimpleSystem() = delete;

        template<typename Container>
        SimpleSystem(Container const &partc, Scalar t) : ptc_(partc, t), acc_(partc.size()) {
            if constexpr (Interactions::is_vel_dep) {
                vel_dep_acc_.resize(partc.size());
                auxi_vel_ = ptc_.vel();
            }
        }

        size_t impl_number() {
            return ptc_.number();
        }

        void impl_advance_time(Scalar dt) {
            ptc_.time() += dt;
        }

        void impl_advance_pos(Coord const &velocity, Scalar stepSize) {
            calc::coord_advance(ptc_.pos(), velocity, stepSize);
        }

        void impl_advance_vel(Coord const &acceleration, Scalar stepSize) {
            calc::coord_advance(ptc_.vel(), acceleration, stepSize);
        }

        void impl_evaluate_acc(Coord &acceleration) {
            eom_.eval_acc(ptc_, acceleration);
        }

        void impl_drift(Scalar stepSize) {
            ptc_.time() += stepSize;
            calc::coord_advance(ptc_.pos(), ptc_.vel(), stepSize);
        }

        void impl_kick(Scalar stepSize) {
            if constexpr (Interactions::is_vel_dep) {
                Scalar halfStep = 0.5 * stepSize;
                eom_.eval_vel_indep_acc(ptc_, acc_);
                kick_pseu_vel(halfStep);
                kick_real_vel(stepSize);
                kick_pseu_vel(halfStep);
            } else {
                eom_.eval_acc(ptc_, acc_);
                calc::coord_advance(ptc_.vel(), acc_, stepSize);
            }
        }

        friend std::ostream &operator<<(std::ostream &os, SimpleSystem const &ps) {
            os << ps.ptc_;
        }
    private:
        void kick_pseu_vel(Scalar stepSize) {
            eom_.eval_extra_vel_dep_acc(ptc_, vel_dep_acc_);
            calc::array_add(acc_, acc_, vel_dep_acc_);
            calc::coord_advance(auxi_vel_, acc_, stepSize);
        }

        void kick_real_vel(Scalar stepSize) {
            std::swap(auxi_vel_, ptc_.vel());
            eom_.eval_extra_vel_dep_acc(ptc_, vel_dep_acc_);
            std::swap(auxi_vel_, ptc_.vel());
            calc::array_add(acc_, acc_, vel_dep_acc_);
            calc::coord_advance(ptc_.vel(), acc_, stepSize);
        }

        Particles ptc_;
        Interactions eom_;
        Coord acc_{0};

        Coord vel_dep_acc_{0};
        Coord auxi_vel_{0};
    };
}

#endif
