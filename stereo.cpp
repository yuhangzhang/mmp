#include "../vxl-1.14.0/core/vil/vil_image_view.h"
#include "../vxl-1.14.0/core/vil/vil_load.h"
#include "../vxl-1.14.0/core/vil/vil_save.h"

//exe imagel imager depth
int main(int argc, char* argv[])
{
	vil_image_view<vxl_byte> iml = vil_load(argv[1]);
	vil_image_view<vxl_byte> imr = vil_load(argv[2]);

}