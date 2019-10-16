/*---------------------------------------------------------------------------*\
        .-''''-.         |
       /        \        |
      /_        _\       |  SpaceHub: The Open Source N-body Toolkit
     // \  <>  / \\      |
     |\__\    /__/|      |  Website:  https://yihanwangastro.github.io/SpaceHub/
      \    ||    /       |
        \  __  /         |  Copyright (C) 2019 Yihan Wang
         '.__.'          |
---------------------------------------------------------------------
License
    This file is part of SpaceHub.
    SpaceHub is free software: you can redistribute it and/or modify it under
    the terms of the MIT License. SpaceHub is distributed in the hope that it
    will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the MIT License
    for more details. You should have received a copy of the MIT License along
    with SpaceHub.
\*---------------------------------------------------------------------------*/
/**
 * @dir src @brief Root
 * @folder{vector}
 * @folder{tools}
 * @folder{stellar}
 * @folder{particles}
 * @folder{particle-system}
 * @folder{orbits}
 * @folder{ode-iterator}
 *   @folder{ode-iterator/error-checker}
 *   @folder{ode-iterator/step-controller}
 * @folder{multi-thread}
 * @folder{lazy-evaluation}
 * @folder{interaction}
 * @folder{integrator}
 *   @folder{integrator/symplectic}
 * @folder{args-callback}
 *
 *
 * @file spaceHub.hpp
 *
 * Giant header file.
 */

#ifndef SPACEHUB_SPACEHUB_HPP
#define SPACEHUB_SPACEHUB_HPP

#include "kahan-number.hpp"
#include "macros.hpp"

#include "particles/finite-size.hpp"
#include "particles/point-particles.hpp"

#include "simulator.hpp"

#include "interaction/newtonian.hpp"

#include "particle-system/archain.hpp"
#include "particle-system/base-system.hpp"
#include "particle-system/chain-system.hpp"
#include "particle-system/regu-system.hpp"

#include "integrator/symplectic/symplectic-integrator.hpp"

#include "ode-iterator/error-checker/RMS.hpp"
#include "ode-iterator/error-checker/worst-offender.hpp"

#include "ode-iterator/step-controller/PID-controller.hpp"

#include "ode-iterator/Burlish-Stoer.hpp"
#include "ode-iterator/const-iterator.hpp"

#include "args-callback/callbacks.hpp"

#include "orbits/orbits.hpp"

#include "tools/auto-name.hpp"
/**
 * @namespace space
 * Documentation for space
 */
namespace space {
using DefaultTypes = Types<double, std::vector>;

template <template <class> class Paticles = particle_set::PointParticles, typename Force = interactions::NewtonianGrav>
using DefaultSolver =
    Simulator<particle_system::ARchainSystem<Paticles<DefaultTypes>, Force, particle_system::ReguType::LogH>,
              ode_iterator::BurlishStoer<double, ode_iterator::RMS, ode_iterator::PIDController>>;

// template<template <class> class Paticles = SoAPointParticles, typename Force = interactions::NewtonianGrav>
// using DefaultSolver = Simulator<ChainSystem<Paticles<DefaultTypes>, Force>, ode_iterator::BurlishStoer<double>>;

// template<template <class> class Paticles = SoAPointParticles, typename Force = interactions::NewtonianGrav>
// using DefaultSolver = Simulator<SimpleSystem<Paticles<DefaultTypes>, Force>, ode_iterator::BurlishStoer<double>>;
}  // namespace space

#endif
