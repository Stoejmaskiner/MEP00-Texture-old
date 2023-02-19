# FP000 - Texture

***product type:** Effect plugin (FP)

***category:** creative effect, sound design*

Texture is a plugin that adds white noise correlated with the input signal. Give it a tonal sound and it will make it a noisy sound.

It has two modes: simple and gritty. Simple mode simply ring modulates white noise to the input and sums it, while gritty mode half-wave rectifies the white noise and squares it to make it more akin dense dust noise; then the dust noise is ring modulated with the rectified version of the input and summed together.

Optionally, the noise can be shaped with gentle 6dB low cut and high cut filters before summing with the input.

<!--
**Block diagram of simple mode**



**Block diagram of gritty mode**



## Shared Processors Used

Texture is a meta-plugin, so it is developed for the purpose of testing code that will be used in larger projects in the future. This "shared code" is encapsulated into objects called "processors", these processors are used across multiple Støjmaskiner products. While other products are closed source, all meta-plugins are open source as well as the shared code library they help develop.

The processors used are the following:

- [RingModNoise]()
- [RingModDust]()
-->

## Roadmap

- Beta pre-release
  - [x] Fully working DSP
  - [x] Fully working GUI
  
- Release
  - [ ] User manual
  - [ ] VST3 exclusive feature integration (right click contextual menu)
  - [ ] Keyboard shortcuts
  - [ ] UX refinement
  - [ ] Bug proofing
  - [ ] SIMD optimization
  - [ ] Custom theme files for advanced users
  - [ ] Save presets as JSON rather than XML
