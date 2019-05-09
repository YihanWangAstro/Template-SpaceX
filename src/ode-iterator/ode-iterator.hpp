//
// Created by yihan on 3/8/19.
//

#ifndef SPACEHUB_ODE_ITERATOR_HPP
#define SPACEHUB_ODE_ITERATOR_HPP

#include "../particle-system.hpp"

namespace space::odeIterator {

    /*---------------------------------------------------------------------------*\
        Class OdeIterator Declaration
    \*---------------------------------------------------------------------------*/
    template<typename Derived>
    class OdeIterator {
    public:
        //Public methods
        template<typename T>
        auto iterate(T &particles, typename T::Scalar macro_step_size) -> typename T::Scalar;

    private:
        //Constructor
        OdeIterator() = default;

        friend Derived;
    };

    /*---------------------------------------------------------------------------*\
        Class OdeIterator Implementation
    \*---------------------------------------------------------------------------*/
    template<typename Derived>
    template<typename T>
    auto OdeIterator<Derived>::iterate(T &particles, typename T::Scalar macro_step_size) -> typename T::Scalar {
        static_assert(is_particle_system_v<T>, "Passing non paritcle-system-type!");
        return static_cast<Derived *>(this)->impl_iterate(particles, macro_step_size);
    }

    /*---------------------------------------------------------------------------*\
        Help functions and tools
    \*---------------------------------------------------------------------------*/
    template<typename T>
    constexpr bool is_ode_iterator_v = std::is_base_of_v<OdeIterator<T>, T>;
}
#endif //SPACEHUB_ODE_ITERATOR_HPP