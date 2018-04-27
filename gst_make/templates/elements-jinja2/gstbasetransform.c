{% extends "gstobject.c" %}

{% set GST_TYPE_CLASS_NAME = "GST_TYPE_BASE_TRANSFORM" %}

{% block includes %}
#include <gst/base/gstbasetransform.h>
{% endblock %}

{% block prototypes %}
/* gstbasetransform prototypes */
static GstCaps *{{r.gst_replace}}_transform_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * filter);
static GstCaps *{{r.gst_replace}}_fixate_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps);
static gboolean {{r.gst_replace}}_accept_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps);
static gboolean {{r.gst_replace}}_set_caps (GstBaseTransform * trans,
    GstCaps * incaps, GstCaps * outcaps);
static gboolean {{r.gst_replace}}_query (GstBaseTransform * trans,
    GstPadDirection direction, GstQuery * query);
static gboolean {{r.gst_replace}}_decide_allocation (GstBaseTransform * trans,
    GstQuery * query);
static gboolean {{r.gst_replace}}_filter_meta (GstBaseTransform * trans,
    GstQuery * query, GType api, const GstStructure * params);
static gboolean {{r.gst_replace}}_propose_allocation (GstBaseTransform * trans,
    GstQuery * decide_query, GstQuery * query);
static gboolean {{r.gst_replace}}_transform_size (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, gsize size, GstCaps * othercaps,
    gsize * othersize);
static gboolean {{r.gst_replace}}_get_unit_size (GstBaseTransform * trans,
    GstCaps * caps, gsize * size);
static gboolean {{r.gst_replace}}_start (GstBaseTransform * trans);
static gboolean {{r.gst_replace}}_stop (GstBaseTransform * trans);
static gboolean {{r.gst_replace}}_sink_event (GstBaseTransform * trans,
    GstEvent * event);
static gboolean {{r.gst_replace}}_src_event (GstBaseTransform * trans,
    GstEvent * event);
static GstFlowReturn {{r.gst_replace}}_prepare_output_buffer (GstBaseTransform *
    trans, GstBuffer * input, GstBuffer ** outbuf);
static gboolean {{r.gst_replace}}_copy_metadata (GstBaseTransform * trans,
    GstBuffer * input, GstBuffer * outbuf);
static gboolean {{r.gst_replace}}_transform_meta (GstBaseTransform * trans,
    GstBuffer * outbuf, GstMeta * meta, GstBuffer * inbuf);
static void {{r.gst_replace}}_before_transform (GstBaseTransform * trans,
    GstBuffer * buffer);
static GstFlowReturn {{r.gst_replace}}_transform (GstBaseTransform * trans,
    GstBuffer * inbuf, GstBuffer * outbuf);
static GstFlowReturn {{r.gst_replace}}_transform_ip (GstBaseTransform * trans,
    GstBuffer * buf);
{% endblock %}

{% block pads %}
static GstStaticPadTemplate {{r.gst_replace}}_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/unknown")
    );

static GstStaticPadTemplate {{r.gst_replace}}_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/unknown")
    );
{% endblock %}

{% block declare_class %}
  GstBaseTransformClass *base_transform_class = GST_BASE_TRANSFORM_CLASS (klass);
{% endblock %}

{% block class_init %}
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS(klass),
      &{{r.gst_replace}}_src_template);

  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS(klass),
      &{{r.gst_replace}}_sink_template);
{% endblock %}

{% block set_methods %}
  base_transform_class->transform_caps = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_transform_caps);
  base_transform_class->fixate_caps = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_fixate_caps);
  base_transform_class->accept_caps = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_accept_caps);
  base_transform_class->set_caps = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_set_caps);
  base_transform_class->query = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_query);
  base_transform_class->decide_allocation = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_decide_allocation);
  base_transform_class->filter_meta = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_filter_meta);
  base_transform_class->propose_allocation = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_propose_allocation);
  base_transform_class->transform_size = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_transform_size);
  base_transform_class->get_unit_size = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_get_unit_size);
  base_transform_class->start = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_start);
  base_transform_class->stop = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_stop);
  base_transform_class->sink_event = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_sink_event);
  base_transform_class->src_event = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_src_event);
  base_transform_class->prepare_output_buffer = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_prepare_output_buffer);
  base_transform_class->copy_metadata = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_copy_metadata);
  base_transform_class->transform_meta = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_transform_meta);
  base_transform_class->before_transform = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_before_transform);
  base_transform_class->transform = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_transform);
  base_transform_class->transform_ip = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_transform_ip);
{% endblock %}

{% block methods %}
static GstCaps *
{{r.gst_replace}}_transform_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, GstCaps * filter)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);
  GstCaps *othercaps;

  GST_DEBUG_OBJECT ({{r.replace}}, "transform_caps");

  othercaps = gst_caps_copy (caps);

  /* Copy other caps and modify as appropriate */
  /* This works for the simplest cases, where the transform modifies one
   * or more fields in the caps structure.  It does not work correctly
   * if passthrough caps are preferred. */
  if (direction == GST_PAD_SRC) {
    /* transform caps going upstream */
  } else {
    /* transform caps going downstream */
  }

  if (filter) {
    GstCaps *intersect;

    intersect = gst_caps_intersect (othercaps, filter);
    gst_caps_unref (othercaps);

    return intersect;
  } else {
    return othercaps;
  }
}

static GstCaps *
{{r.gst_replace}}_fixate_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, GstCaps * othercaps)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "fixate_caps");

  return NULL;
}

static gboolean
{{r.gst_replace}}_accept_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "accept_caps");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "set_caps");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_query (GstBaseTransform * trans, GstPadDirection direction,
    GstQuery * query)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "query");

  return TRUE;
}

/* decide allocation query for output buffers */
static gboolean
{{r.gst_replace}}_decide_allocation (GstBaseTransform * trans, GstQuery * query)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "decide_allocation");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_filter_meta (GstBaseTransform * trans, GstQuery * query, GType api,
    const GstStructure * params)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "filter_meta");

  return TRUE;
}

/* propose allocation query parameters for input buffers */
static gboolean
{{r.gst_replace}}_propose_allocation (GstBaseTransform * trans,
    GstQuery * decide_query, GstQuery * query)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "propose_allocation");

  return TRUE;
}

/* transform size */
static gboolean
{{r.gst_replace}}_transform_size (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, gsize size, GstCaps * othercaps, gsize * othersize)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "transform_size");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_get_unit_size (GstBaseTransform * trans, GstCaps * caps,
    gsize * size)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "get_unit_size");

  return TRUE;
}

/* states */
static gboolean
{{r.gst_replace}}_start (GstBaseTransform * trans)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "start");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_stop (GstBaseTransform * trans)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "stop");

  return TRUE;
}

/* sink and src pad event handlers */
static gboolean
{{r.gst_replace}}_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "sink_event");

  return GST_BASE_TRANSFORM_CLASS ({{r.gst_replace}}_parent_class)->sink_event (
      trans, event);
}

static gboolean
{{r.gst_replace}}_src_event (GstBaseTransform * trans, GstEvent * event)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "src_event");

  return GST_BASE_TRANSFORM_CLASS ({{r.gst_replace}}_parent_class)->src_event (
      trans, event);
}

static GstFlowReturn
{{r.gst_replace}}_prepare_output_buffer (GstBaseTransform * trans, GstBuffer * input,
    GstBuffer ** outbuf)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "prepare_output_buffer");

  return GST_FLOW_OK;
}

/* metadata */
static gboolean
{{r.gst_replace}}_copy_metadata (GstBaseTransform * trans, GstBuffer * input,
    GstBuffer * outbuf)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "copy_metadata");

  return TRUE;
}

static gboolean
{{r.gst_replace}}_transform_meta (GstBaseTransform * trans, GstBuffer * outbuf,
    GstMeta * meta, GstBuffer * inbuf)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "transform_meta");

  return TRUE;
}

static void
{{r.gst_replace}}_before_transform (GstBaseTransform * trans, GstBuffer * buffer)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "before_transform");

}

/* transform */
static GstFlowReturn
{{r.gst_replace}}_transform (GstBaseTransform * trans, GstBuffer * inbuf,
    GstBuffer * outbuf)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "transform");

  return GST_FLOW_OK;
}

static GstFlowReturn
{{r.gst_replace}}_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  {{r.GstReplace}} *{{r.replace}} = {{r.GST_REPLACE}} (trans);

  GST_DEBUG_OBJECT ({{r.replace}}, "transform_ip");

  return GST_FLOW_OK;
}
{% endblock %}
