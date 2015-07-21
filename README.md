# TexturesXMLExporter

TexturesXMLExporter aims to extract all textures to an xml file, formatted to be loaded by javascript to present the textures as a webpage.

## Requirements
* ImageMagick ( http://www.imagemagick.org/ )
ImageMagick is used to create the thumbnails of the textures. It can either be installed in the system, or provided in a portable version which can be used with the -im argument (see Optional command line arguments).


## Documentation
Drop the executable file inside the folder where the textures are being kept. Then execute it.
TexturesXMLExporter creates a folder in the root path named exp_thumbs, which will contain all the thumbnails of all textures which will be created. All thumbnails will be in png file type and size of 200 width and 200 height.
A file textures.xml will be generated with all the textures and their thumbnails in it.

### Supported textures extensions
* .png
* .jpg
* .tif
* .tga
* .psd
* .svg

### Supported textures suffixes
| Map Type   | Suffixes
| ---------- | ----------------------
| Diffuse    | _d
| Bump       | _bmp
| Normal     | _normal, _n, _N, _nY+
| Gloss      | _g
| Height     | _h, _H
| Specular   | _s, _S
| Roughness  | _r, _R
| Metalness  | m, _MT

### Optional command line arguments
* -p
	Followed by a folder path it is used to use a custom path instead of the one the program is into.
	Example: "TexturesXMLExporter.exe -p C:\Users\Me\Textures"
	The thumbs folder and the textures.xml file will be generated to the custom path.
* -im
	Uses a local version of ImageMagick. Specifically requires the full path of the executable convert.exe.
	Example: "TexturesXMLExporter.exe -im C:\Users\Me\Downloads\ImageMagick-6.9.1-9-portable-Q16-x64\convert.exe"
* --version
	Prints out version of the program.
* --help
	Shows available parameters when executing from command line.


## Tips
* TexturesXMLExporter checks existing thumbnails before it creates new ones. If a thumbnail exists it doesn't create a new one. If you wish to refresh a thumbnail (eg. if you changed the source texture), you can simply delete the thumbnail and re-run the executable to re-create it.


## Notes
* Symbol & causes problems in the xml format. It is replaced by &amp; .


## Todo
* Check how to suppress ImageMagick messages in the command line.
* Copyright
* License