# gst-make

Command line tool for creating gstreamer plugin projects. Heavily based on the tools from `gstreamer-plugins-bad`.

## Getting Started

These tools consists of a collection of shell scripts for generating gstreamer plugin projects, plugins and elements.

```bash
git clone https://github.com/ast/gst-make.git
cd gst-make
# to install an editable (development) version:
pip3 install -e .  
```

Should also be possible to install like a normal python packge but it's not stable yet, so **not recommended**.

```bash
pip3 install gst-make
```

### Using

```bash
# create project
cd
gst-make project my_project
cd gst-my_project

# build with meson
meson build
# and ninja
ninja -C build

# add a plugin
cd gst
gst-make plugin myplugin
# add this plugin to meson.build
echo "subdir('myplugin')" >> meson.build

# rebuild with plugin
ninja -C ../build

cd myplugin
# add an element
gst-make element my_element basetransform
# add gstmyelement.c to meson.build and rebuild

# add to gstreamer plugin search path
export GST_PLUGIN_PATH = $HOME/gst-my_project/build/gst/myplugin:$GST_PLUGIN_PATH
```


### Prerequisites

You will need:

* python3
* gstreamer
* meson
* ninja

## TODO

* The naming of projects and plugins is not optimal.
* Some of the element templates are out of date.
* Probably a lot of other bugs.

## Built With

* [gstreamer](https://gstreamer.freedesktop.org/) - Best media framework in this galaxy.
* [meson](http://mesonbuild.com/) - The Meson Build system
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Feedback and pull-requests are very welcome.

## Versioning

Still too early.

## Authors

* **Albin Stigö** - *Initial work* - [ast](https://github.com/ast)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

LGPL

## Acknowledgments

* gstreamer team

