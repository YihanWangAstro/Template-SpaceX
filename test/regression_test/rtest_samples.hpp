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
#ifndef SPACEHUB_RTEST_SAMPLES_HPP
#define SPACEHUB_RTEST_SAMPLES_HPP

#include "../../src/spaceHub.hpp"

#include <iomanip>
#include <tuple>

template <typename Solver>
auto two_body(double e = 0) {
  using Particle = typename Solver::Particle;
  using namespace space;
  using namespace space::unit;
  using namespace space::orbit;

  Particle sun{1_Ms}, earth{1_Me};
  auto orbit = EllipOrbit(sun.mass, earth.mass, 1_AU, e, 0, 0, 0, 0);

  move_particles(orbit, earth);

  move_to_COM_frame(sun, earth);

  return std::vector{sun, earth};
}

template <typename Solver>
auto earth_system() {
  using Particle = typename Solver::Particle;
  using namespace space;
  using namespace space::unit;
  using namespace space::orbit;

  Particle sun{1_Ms}, earth{1_Me}, moon{1_Mmoon};

  auto moon_orbit = EllipOrbit(earth.mass, moon.mass, 384748_km, 0.0549006, 5.15_deg, 0, 0, 0);

  move_particles(moon_orbit, moon);

  auto orbit = EllipOrbit(sun.mass, earth.mass + moon.mass, 1_AU, 0, 0, 0, 0, 0);

  move_particles(orbit, earth, moon);

  move_to_COM_frame(sun, earth, moon);

  return std::vector{sun, earth, moon};
}

template <typename Solver>
auto kozai() {
  using Particle = typename Solver::Particle;
  using namespace space;
  using namespace space::unit;
  using namespace space::orbit;

  Particle m1{1.4_Ms}, m2{0.3_Ms}, m3{0.01_Ms};

  auto in_orbit = EllipOrbit(m1.mass, m2.mass, 5_AU, 0.5, 0, 0, 120_deg, 0);

  move_particles(in_orbit, m2);

  move_to_COM_frame(m1, m2);

  auto out_orbit = EllipOrbit(m1.mass + m2.mass, m3.mass, 50_AU, 0, 80.8_deg, 0, 0, 0);

  move_particles(out_orbit, m3);

  move_to_COM_frame(m1, m2, m3);

  return std::vector{m1, m2, m3};
}

template <typename Solver>
auto outer_solar() {
  using Particle = typename Solver::Particle;
  using namespace space;
  using namespace space::unit;
  using namespace space::orbit;
  // data is from wikipedia https://en.wikipedia.org/wiki/Solar_System TODO: use mean anomaly as true anomaly.
  Particle sun{1_Ms}, jupiter{1_Mj}, saturn{95.159_Me}, uranus{14.536_Me}, neptune{17.147_Me};

  auto j_orbit = EllipOrbit(sun.mass, jupiter.mass, 5.2044_AU, 0.0489, 6.09_deg, 100.464_deg, 273.867_deg, 20.02_deg);
  move_particles(j_orbit, jupiter);

  auto s_orbit = EllipOrbit(sun.mass, saturn.mass, 9.5826_AU, 0.0565, 5.51_deg, 113.665_deg, 339.392_deg, 317.02_deg);
  move_particles(j_orbit, saturn);

  auto u_orbit =
      EllipOrbit(sun.mass, uranus.mass, 19.2184_AU, 0.046381, 6.48_deg, 74.006_deg, 96.998857_deg, 142.2386_deg);
  move_particles(j_orbit, uranus);

  auto n_orbit =
      EllipOrbit(sun.mass, neptune.mass, 30.11_AU, 0.009456, 6.43_deg, 131.784_deg, 276.336_deg, 256.228_deg);
  move_particles(j_orbit, neptune);

  move_to_COM_frame(sun, jupiter, saturn, uranus, neptune);

  return std::vector{sun, jupiter, saturn, uranus, neptune};
}

template <typename Solver>
void basic_error_test(std::string const &fname, double end_time, double rtol,
                      std::vector<typename Solver::Particle> const &p) {
  using namespace space;
  using namespace run_operations;
  using namespace tools;

  Solver sim{0, p};

  typename Solver::RunArgs args;

  std::ofstream err_file(fname + ".err");

  err_file << std::setprecision(16);

  auto E0 = calc::calc_total_energy(sim.particles());

  double tot_error = 0;

  size_t error_num = 0;

  args.rtol = rtol;

  args.add_pre_step_operation(TimeSlice(
      [&](auto &ptc, auto step_size) {
        auto err = calc::calc_energy_error(ptc, E0);
        tot_error += err * err;
        error_num++;
        err_file << ptc.time() << ',' << err << '\n';
      },
      0, end_time));

  args.add_stop_condition(end_time);

  Timer timer;

  timer.start();

  sim.run(args);

  std::cout << "The mean relative error of test: " + fname + " : " << sqrt(tot_error / error_num) << "\n";
  std::cout << "time : " << timer.get_time() << " s\n";
}

template <typename Solver>
auto error_scale(double rtol_start, double rtol_end, double end_time, std::vector<typename Solver::Particle> const &p) {
  using namespace space;
  using namespace run_operations;
  using namespace tools;

  size_t n = static_cast<size_t>(log(rtol_end / rtol_start) / log(2)) + 1;

  std::vector<double> rtol(n);
  std::vector<double> err(n);

  multi_thread::indexed_multi_thread(n, [&](size_t thid) {
    typename Solver::RunArgs args;

    double tot_error = 0;

    size_t error_num = 0;

    auto E0 = orbit::E_tot(p);  // calc::calc_total_energy(sim.particles());

    args.add_pre_step_operation([&](auto &ptc, auto step_size) {
      auto err = calc::calc_energy_error(ptc, E0);
      tot_error += err * err;
      error_num++;
    });

    args.add_stop_condition(end_time);

    args.rtol = rtol_start * pow(2, thid);

    Solver sim{0, p};
    sim.run(args);

    rtol[thid] = args.rtol;
    err[thid] = sqrt(tot_error / error_num);
  });

  return std::make_tuple(rtol, err);
}

#endif  // SPACEHUB_RTEST_SAMPLES_HPP