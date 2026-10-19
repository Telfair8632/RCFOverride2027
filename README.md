# RCF Override 2027 — VEX V5 Competition Robot Code

Competition code for our team's VEX V5 robot in the **RCF Override (2026–27) season**, written in C++ on the [PROS](https://pros.cs.purdue.edu/) kernel. Developed by a three-person team over the build season (July–October 2026).

## What's in here

| Path | Contents |
|---|---|
| `src/auto/` | 9 competition autonomous routines — programming skills plus red/blue left/right, two variants each |
| `src/motorcontrol/` | `chassis` (tank drive), `lift` (position-based control with rotation sensor), and a shared `pid` controller |
| `src/display/` | `logger` — thread-safe on-brain LCD log viewer with paging |
| `src/main.cpp` | Competition template: initialization, autonomous dispatch, driver control, autonomous selector |
| `include/haws/` | Hardware configuration (motor groups, IMU, pneumatics) and module headers |

## Autonomous selection

- `autoSelection` in `src/main.cpp` sets the default routine run by `autonomous()` (`1` = red-left variant 1).
- Set `isSelectAuto = true` to enable the on-controller selector at the field: **LEFT/RIGHT** cycles through the 9 routines shown on the controller screen, **B** confirms.

## Hardware map (V5 brain)

| Subsystem | Ports |
|---|---|
| Drive — left | motor group −15, −14, 13 |
| Drive — right | motor group 16, 12, −11 |
| Lift | motor group 3, −4 |
| Lift rotation sensor | −2 |
| Roller intake | −20 |
| Arm | 4 |
| IMU (inertial) | 18 |
| Pneumatic clip | ADI port B |

## Building

Requires the [PROS CLI](https://pros.cs.purdue.edu/v5/getting-started/):

```bash
pros make      # build
pros upload    # flash to the brain
```

## License

MIT — see [LICENSE](LICENSE). © 2026 RCF Override 2027 Team.
