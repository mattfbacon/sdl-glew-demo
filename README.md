# SDL/GLEW Experimentation

This project was an experiment in GLSL shaders, as well as the GLEW and SDL libraries.

I began by writing wrappers for all of the SDL and GLEW "objects" I used, such as SDL windows, GLEW shaders, and GLEW programs.

Then I wrote a wrapper for a file mapped with `mmap`, in order to `mmap` the vertex and fragment shaders.

After loading, compiling, and linking the GLSL shaders, they are rendered to an SDL window in the shape of an isoceles triangle.

The classes are documented to hopefully be useful to others.

## Build/Run

```bash
make release
# in root dir
./dist/Release/opengl
```

## License

As this is a project for fun, it's licensed under the WTFPL. For more info,see `LICENSE`.
