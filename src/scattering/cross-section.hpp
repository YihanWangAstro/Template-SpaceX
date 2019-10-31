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
 * @file cross-section.hpp
 *
 * Header file.
 */
#ifndef SPACEHUB_CROSS_SECTION_HPP
#define SPACEHUB_CROSS_SECTION_HPP

#include "../orbits/orbits.hpp"
#include "../orbits/particle-manip.hpp"
#include "../rand-generator.hpp"
#include "../vector/vector3.hpp"

/**
 * @namespace space::scattering
 * namespace for scattering
 */
namespace space::scattering {

template <typename Scalar>
auto critical_vel(Scalar m1, Scalar m2, Scalar E1_inner, Scalar E2_inner) {
  auto m_rdc = m1 * m2 / (m1 + m2);
  return sqrt(-2 * (E1_inner + E2_inner) / m_rdc);
}

template <typename Cluster1, typename Cluster2>
auto critical_vel(Cluster1 const& stay_cluster, Cluster2 const& incident_cluster) {
  auto M_stay = orbit::M_tot(stay_cluster);
  auto M_incident = orbit::M_tot(incident_cluster);
  auto E_inner1 = orbit::E_inner(stay_cluster);
  auto E_inner2 = orbit::E_inner(incident_cluster);
  return critical_vel(M_stay, M_incident, E_inner1, E_inner2);
}

/*template <typename Scalar>
auto b_max(Scalar v_c, Scalar v_inf, Scalar a_max) {
  return a_max * (8 * v_c / v_inf + 3);
}*/

template <typename Scalar>
auto b_max(Scalar m_tot, Scalar v_inf, Scalar rp_max) {
  return sqrt(rp_max * rp_max + 2 * m_tot * consts::G * rp_max / (v_inf * v_inf));
}

template <typename Scalar>
auto incident_orbit(Scalar m_stay, Scalar m_incident, Scalar v_inf, Scalar b_max, Scalar r) {
  using Vector = Vec3<Scalar>;
  auto b = sqrt(random::Uniform(0, b_max * b_max));
  auto w = random::Uniform(0, 2 * consts::pi);
  return orbit::HyperOrbit(m_stay, m_incident, v_inf, b, w, 0, 0, r, orbit::Hyper::in);
}

template <typename Cluster1, typename Cluster2, typename Scalar>
auto incident_orbit(Cluster1 const& stay_cluster, Cluster2 const& incident_cluster, Scalar v_inf, Scalar tidal_factor) {
  auto const M_stay = orbit::M_tot(stay_cluster);
  auto const M_incident = orbit::M_tot(incident_cluster);

  auto const R1 = orbit::cluster_size(stay_cluster);
  auto const R2 = orbit::cluster_size(incident_cluster);

  Scalar interact_factor = 0.02;
  auto const R_max = orbit::tidal_radius(interact_factor, M_stay, M_incident, R1, R2);

  auto const b_upper = b_max(M_stay + M_incident, v_inf, R_max);

  auto const r_start = orbit::tidal_radius(tidal_factor, M_stay, M_incident, R1, R2);
  return incident_orbit(M_stay, M_incident, v_inf, b_upper, r_start);
}

template <typename Cluster1, typename Cluster2, typename Scalar>
auto incident_orbit(Cluster1 const& stay_cluster, Cluster2 const& incident_cluster, Scalar v_inf, Scalar b_max,
                    Scalar tidal_factor) {
  auto const M_stay = orbit::M_tot(stay_cluster);
  auto const M_incident = orbit::M_tot(incident_cluster);
  auto const R1 = orbit::cluster_size(stay_cluster);
  auto const R2 = orbit::cluster_size(incident_cluster);

  auto const r_start = orbit::tidal_radius(tidal_factor, M_stay, M_incident, R1, R2);

  return incident_orbit(M_stay, M_incident, v_inf, b_max, r_start);
}

template <typename Scalar>
inline auto hard_radius(Scalar m1, Scalar m2, Scalar m_evn, Scalar sigma) {
  return consts::G * m1 * m2 / (m_evn * sigma * sigma);
}

}  // namespace space::scattering

#endif  // SPACEHUB_CROSS_SECTION_HPP
