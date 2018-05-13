This script needs to run in a web server
Create your compiled binary (from Arduino IDE - Sketch/Export Compiled Binary)

IN THIS ORDER!

copy it to bin/sv.<your version number>.bin
Then update svUpdate.php to change $currentVersion = <your version number>

If you do that part backwards, there's a chance that a partial file will be
sent, forcing you to reset and upload the binary over FTDI again.

