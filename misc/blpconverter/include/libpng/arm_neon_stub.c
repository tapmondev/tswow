/* Stub implementation of ARM NEON filter functions for macOS */
#include "pngpriv.h"

/* This is a stub implementation of the NEON optimized filter functions
 * for macOS on Apple Silicon. The real implementation would be in
 * arm/filter_neon.S, but we don't have that file, so we provide this
 * stub that does nothing.
 */
void
png_init_filter_functions_neon(png_structp png_ptr, unsigned int bpp)
{
    /* Do nothing - this is just a stub to satisfy the linker */
    PNG_UNUSED(png_ptr)
    PNG_UNUSED(bpp)
}