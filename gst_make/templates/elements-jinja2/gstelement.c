{% extends "gstobject.c" %}

{% set GST_TYPE_CLASS_NAME = "GST_TYPE_ELEMENT" %}

{% block includes %}
#include <gst/gst.h>
{% endblock %}

{% block prototypes %}
/* GstElement */
static GstPad *{{r.gst_replace}}_request_new_pad (GstElement *element, GstPadTemplate *templ,
                                                 const gchar* name, const GstCaps *caps);
static void {{r.gst_replace}}_release_pad (GstElement * element, GstPad * pad);
static GstStateChangeReturn
{{r.gst_replace}}_change_state (GstElement * element, GstStateChange transition);
static GstClock *{{r.gst_replace}}_provide_clock (GstElement * element);
static gboolean {{r.gst_replace}}_set_clock (GstElement * element, GstClock * clock);
static gboolean {{r.gst_replace}}_send_event (GstElement * element, GstEvent * event);
static gboolean {{r.gst_replace}}_query (GstElement * element, GstQuery * query);

/* Sinkpad */
static gboolean {{r.gst_replace}}_sink_activate (GstPad *pad, GstObject *parent);
static GstPadLinkReturn {{r.gst_replace}}_sink_link (GstPad *pad, GstObject *parent, GstPad *peer);
static void {{r.gst_replace}}_sink_unlink (GstPad *pad, GstObject *parent);
static GstFlowReturn {{r.gst_replace}}_sink_chain (GstPad *pad, GstObject *parent, GstBuffer *buffer);
static GstFlowReturn {{r.gst_replace}}_sink_chainlist (GstPad *pad, GstObject *parent, GstBufferList *bufferlist);
static gboolean {{r.gst_replace}}_sink_event (GstPad *pad, GstObject *parent, GstEvent *event);
static gboolean {{r.gst_replace}}_sink_query (GstPad *pad, GstObject *parent, GstQuery *query);
static GstIterator * {{r.gst_replace}}_sink_iterintlink (GstPad *pad, GstObject *parent);

/* Source pad */
static gboolean {{r.gst_replace}}_src_activate (GstPad *pad, GstObject *parent);
static GstPadLinkReturn {{r.gst_replace}}_src_link (GstPad *pad, GstObject *parent, GstPad *peer);
static void {{r.gst_replace}}_src_unlink (GstPad *pad, GstObject *parent);
static GstFlowReturn {{r.gst_replace}}_src_getrange (GstPad *pad, GstObject *parent, guint64 offset, guint length,
    GstBuffer **buffer);
static gboolean {{r.gst_replace}}_src_event (GstPad *pad, GstObject *parent, GstEvent *event);
static gboolean {{r.gst_replace}}_src_query (GstPad *pad, GstObject *parent, GstQuery *query);
static GstIterator * {{r.gst_replace}}_src_iterintlink (GstPad *pad, GstObject *parent);
{% endblock %}

{% block pads %}
static GstStaticPadTemplate {{r.gst_replace}}_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/unknown")
    );

static GstStaticPadTemplate {{r.gst_replace}}_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/unknown")
    );
{% endblock %}

{% block declare_class %}
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
{% endblock %}

{% block class_init %}{% endblock %}

{% block set_methods %}
  element_class->request_new_pad = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_request_new_pad);
  element_class->release_pad = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_release_pad);
  element_class->change_state = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_change_state);
  element_class->provide_clock = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_provide_clock);
  element_class->set_clock = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_set_clock);
  element_class->send_event = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_send_event);
  element_class->query = GST_DEBUG_FUNCPTR ({{r.gst_replace}}_query);
{% endblock %}

{% block instance_init %}
  {{r.replace}}->sinkpad = gst_pad_new_from_static_template (&{{r.gst_replace}}_sink_template, "sink");
  gst_pad_set_activate_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_activate));
  gst_pad_set_link_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_link));
  gst_pad_set_unlink_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_unlink));
  gst_pad_set_chain_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_chain));
  gst_pad_set_chain_list_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_chainlist));
  gst_pad_set_event_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_event));
  gst_pad_set_query_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_query));
  gst_pad_set_iterate_internal_links_function ({{r.replace}}->sinkpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_sink_iterintlink));
  /* add pad */
  gst_element_add_pad (GST_ELEMENT({{r.replace}}), {{r.replace}}->sinkpad);


  {{r.replace}}->srcpad = gst_pad_new_from_static_template (&{{r.gst_replace}}_src_template, "src");
  gst_pad_set_activate_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_activate));
  gst_pad_set_link_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_link));
  gst_pad_set_unlink_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_unlink));
  gst_pad_set_getrange_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_getrange));
  gst_pad_set_event_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_event));
  gst_pad_set_query_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_query));
  gst_pad_set_iterate_internal_links_function ({{r.replace}}->srcpad,
            GST_DEBUG_FUNCPTR({{r.gst_replace}}_src_iterintlink));
  /* add pad */
  gst_element_add_pad (GST_ELEMENT({{r.replace}}), {{r.replace}}->srcpad);
{% endblock %}


{% block methods %}

static GstPad *
{{r.gst_replace}}_request_new_pad (GstElement *element, GstPadTemplate *templ,
  const gchar* name, const GstCaps *caps)
{
  return NULL;
}

static void
{{r.gst_replace}}_release_pad (GstElement * element, GstPad * pad)
{
}

static GstStateChangeReturn
{{r.gst_replace}}_change_state (GstElement * element, GstStateChange transition)
{
  {{r.GstReplace}} *{{r.replace}};
  GstStateChangeReturn ret;

  g_return_val_if_fail ({{r.GST_IS_REPLACE}} (element), GST_STATE_CHANGE_FAILURE);
  {{r.replace}}= {{r.GST_REPLACE}} (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS ({{r.gst_replace}}_parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  return ret;
}

static GstClock *
{{r.gst_replace}}_provide_clock (GstElement * element)
{

  return NULL;
}

static gboolean
{{r.gst_replace}}_set_clock (GstElement * element, GstClock * clock)
{

  return GST_ELEMENT_CLASS ({{r.gst_replace}}_parent_class)->set_clock (element, clock);
}

static gboolean
{{r.gst_replace}}_send_event (GstElement * element, GstEvent * event)
{

  return TRUE;
}

static gboolean
{{r.gst_replace}}_query (GstElement * element, GstQuery * query)
{
  {{r.GstReplace}} *{{r.replace}}= {{r.GST_REPLACE}} (element);
  gboolean ret;

  GST_DEBUG_OBJECT ({{r.replace}}, "query");

  switch (GST_QUERY_TYPE (query)) {
    default:
      ret = GST_ELEMENT_CLASS ({{r.gst_replace}}_parent_class)->query (element, query);
      break;
  }

  return ret;
}


static gboolean
{{r.gst_replace}}_sink_activate (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};
  gboolean ret = TRUE;

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "activate");

  gst_object_unref ({{r.replace}});
  return ret;
}

static GstPadLinkReturn
{{r.gst_replace}}_sink_link (GstPad *pad, GstObject *parent, GstPad *peer)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "link");


  gst_object_unref ({{r.replace}});
  return GST_PAD_LINK_OK;
}

static void
{{r.gst_replace}}_sink_unlink (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "unlink");


  gst_object_unref ({{r.replace}});
}

static GstFlowReturn
{{r.gst_replace}}_sink_chain (GstPad *pad, GstObject *parent, GstBuffer *buffer)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "chain");


  gst_object_unref ({{r.replace}});
  return GST_FLOW_OK;
}

static GstFlowReturn
{{r.gst_replace}}_sink_chainlist (GstPad *pad, GstObject *parent, GstBufferList *bufferlist)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "chainlist");


  gst_object_unref ({{r.replace}});
  return GST_FLOW_OK;
}

static gboolean
{{r.gst_replace}}_sink_event (GstPad *pad, GstObject *parent, GstEvent *event)
{
  gboolean res;
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}} = {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "event");

  switch (GST_EVENT_TYPE (event)) {
    default:
      res = gst_pad_event_default (pad, GST_OBJECT({{r.replace}}), event);
      break;
  }

  gst_object_unref ({{r.replace}});
  return res;
}

static gboolean
{{r.gst_replace}}_sink_query (GstPad *pad, GstObject *parent, GstQuery *query)
{
  gboolean res;
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "query");

  switch (GST_QUERY_TYPE(query)) {
    default:
      res = gst_pad_query_default (pad, GST_OBJECT({{r.replace}}), query);
      break;
  }

  gst_object_unref ({{r.replace}});
  return res;
}

static GstIterator *
{{r.gst_replace}}_sink_iterintlink (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};
  GstIterator *iter;

  {{r.replace}} = {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "iterintlink");

  iter = gst_pad_iterate_internal_links_default (pad, parent);

  gst_object_unref ({{r.replace}});
  return iter;
}

static gboolean
{{r.gst_replace}}_src_activate (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};
  gboolean ret = TRUE;

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "activate");

  gst_object_unref ({{r.replace}});
  return ret;
}

static GstPadLinkReturn
{{r.gst_replace}}_src_link (GstPad *pad, GstObject *parent, GstPad *peer)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "link");

  gst_object_unref ({{r.replace}});
  return GST_PAD_LINK_OK;
}

static void
{{r.gst_replace}}_src_unlink (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "unlink");


  gst_object_unref ({{r.replace}});
}

static GstFlowReturn
{{r.gst_replace}}_src_getrange (GstPad *pad, GstObject *parent, guint64 offset, guint length,
    GstBuffer **buffer)
{
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}}= {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "getrange");

  gst_object_unref ({{r.replace}});
  return GST_FLOW_OK;
}

static gboolean
{{r.gst_replace}}_src_event (GstPad *pad, GstObject *parent, GstEvent *event)
{
  gboolean res;
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}} = {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "event");

  switch (GST_EVENT_TYPE (event)) {
    default:
      res = gst_pad_event_default (pad, parent, event);
      break;
  }

  gst_object_unref ({{r.replace}});
  return res;
}

static gboolean
{{r.gst_replace}}_src_query (GstPad *pad, GstObject *parent, GstQuery *query)
{
  gboolean res;
  {{r.GstReplace}} *{{r.replace}};

  {{r.replace}} = {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "query");

  switch (GST_QUERY_TYPE(query)) {
    default:
      res = gst_pad_query_default (pad, parent, query);
      break;
  }

  gst_object_unref ({{r.replace}});
  return res;
}

static GstIterator *
{{r.gst_replace}}_src_iterintlink (GstPad *pad, GstObject *parent)
{
  {{r.GstReplace}} *{{r.replace}};
  GstIterator *iter;

  {{r.replace}} = {{r.GST_REPLACE}} (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT({{r.replace}}, "iterintlink");

  iter = gst_pad_iterate_internal_links_default (pad, parent);

  gst_object_unref ({{r.replace}});
  
  return iter;
}

{% endblock %}
