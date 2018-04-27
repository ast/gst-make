/* GStreamer
 * Copyright (C) $(date +%Y) $REAL_NAME <$EMAIL_ADDRESS>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-${{r. gstreplace }}
 *
 * The $replace element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! $replace ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
{% block includes %}{% endblock %}
#include "{{r.gstreplace}}.h"

GST_DEBUG_CATEGORY_STATIC ({{r.gst_replace}}_debug_category);
#define GST_CAT_DEFAULT {{r.gst_replace}}_debug_category

/* gstobject prototypes */
static void {{r.gst_replace}}_set_property (GObject * object,
  guint property_id, const GValue * value, GParamSpec * pspec);
static void {{r.gst_replace}}_get_property (GObject * object,
  guint property_id, GValue * value, GParamSpec * pspec);
static void {{r.gst_replace}}_dispose (GObject * object);
static void {{r.gst_replace}}_finalize (GObject * object);

{% block prototypes %}{% endblock %}

enum
{
  PROP_0
};

{% block pads %}{% endblock %}

/* class initialization */
G_DEFINE_TYPE_WITH_CODE ({{r.GstReplace}}, {{r.gst_replace}},
  {{GST_TYPE_CLASS_NAME if GST_TYPE_CLASS_NAME else "GST_TYPE_OBJECT"}},
  GST_DEBUG_CATEGORY_INIT ({{r.gst_replace}}_debug_category, "{{r.prefixreplace}}", 0,
  "debug category for replace element"));

static void
{{r.gst_replace}}_class_init ({{r.GstReplace}}Class * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  {% block declare_class %}{% endblock %}

  {% block class_init %}{% endblock %}

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "$REAL_NAME <$EMAIL_ADDRESS>");

  /* GstObject methods */
  gobject_class->set_property = {{r.gst_replace}}_set_property;
  gobject_class->get_property = {{r.gst_replace}}_get_property;
  gobject_class->dispose = {{r.gst_replace}}_dispose;
  gobject_class->finalize = {{r.gst_replace}}_finalize;
  
  {% block set_methods %}{% endblock %}
}


static void
{{r.gst_replace}}_init ({{r.GstReplace}} *{{r.replace}})
{
  {% block instance_init %}{% endblock %}
}

/* GstObject methods */
void
{{r.gst_replace}}_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (object);

  GST_DEBUG_OBJECT ({{r.replace}}, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
{{r.gst_replace}}_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (object);

  GST_DEBUG_OBJECT ({{r.replace}}, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
{{r.gst_replace}}_dispose (GObject * object)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (object);

  GST_DEBUG_OBJECT ({{r.replace}}, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS ({{r.gst_replace}}_parent_class)->dispose (object);
}

void
{{r.gst_replace}}_finalize (GObject * object)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (object);

  GST_DEBUG_OBJECT ({{r.replace}}, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS ({{r.gst_replace}}_parent_class)->finalize (object);
}

/* subclass methods */
{% block methods %}{% endblock %}
