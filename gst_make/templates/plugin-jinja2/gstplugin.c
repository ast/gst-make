#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gst/gst.h>

static gboolean
plugin_init (GstPlugin * plugin)
{
  return TRUE;
}

GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    {{r.replace}},
    "FIXME Template plugin",
    plugin_init,
    VERSION,
    "LGPL", /* FIXME */
    "GStreamer",
    "http://gstreamer.net/"
)
