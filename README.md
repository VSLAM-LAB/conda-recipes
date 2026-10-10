# conda-recipes

Conda package definitions for third-party libraries used by [VSLAM-LAB](https://github.com/VSLAM-LAB/VSLAM-LAB),
built and published to [prefix.dev/vslamlab/vslamlab](https://prefix.dev/channels/@vslamlab/vslamlab) by CI.

Libraries that VSLAM-LAB develops (e.g. `lietorch`, `droidslam`, `dpvo`) keep their package definition in their own
fork instead. This repository is for code that is only packaged, at a fixed commit: upstream as is, or a fork that
carries nothing but build fixes (portable flags, install rules, CMake config).

## Layout

One folder per package, each with a `pixi.toml` that holds:

- `[package]`: the conda package (pixi-build), built from the upstream repository at a pinned `rev`;
- a small workspace whose `test` task installs the package and checks it (C++ libraries: `test/` is a CMake project
  compiled against the installed package through its CMake config);
- `LICENSE` when the package declares a `license-file` (pixi resolves it relative to the folder, not the source).

| Package | Upstream | Version |
|---|---|---|
| `pypose` | [pypose/pypose](https://github.com/pypose/pypose) | 0.7.3 (noarch) |
| `roma` | [naver/roma](https://github.com/naver/roma) | 1.5.2.1 (noarch) |
| `brisk` | [alejandrofontan/brisk](https://github.com/alejandrofontan/brisk) (Leutenegger, ETH ASL) | 1.0.0 (C++, OpenCV 4.12) |
| `akaze` | [alejandrofontan/akaze](https://github.com/alejandrofontan/akaze) (fork of pablofdezalc/akaze) | 1.0.0 (C++, OpenCV 4.12) |
| `siftgpu` | [alejandrofontan/siftgpu](https://github.com/alejandrofontan/siftgpu) (Changchang Wu) | 1.0.0 (C++/CUDA, CUDA 12.6 and 12.9 builds; research / non-profit license) |

## Building locally

```bash
pixi publish --clean --path pypose/pixi.toml --target-dir out/pypose   # build
pixi run --manifest-path pypose/pixi.toml test                          # test
```

## Releasing

CI (`.github/workflows/conda-package.yml`) builds and tests every package on pushes to `main`. To publish one:

1. set `version` in `<package>/pixi.toml` (and the `rev` it builds), commit, push to `main`;
2. tag it as `<package>-vX.Y.Z` and push the tag, e.g.

   ```bash
   git tag -a pypose-v0.7.3 -m "pypose 0.7.3"
   git push origin pypose-v0.7.3
   ```

CI checks the tag against `<package>/pixi.toml`, builds, tests and uploads to `vslamlab/vslamlab` via trusted
publishing. Never move a tag or overwrite a published package: bump the version (or build number) instead.
