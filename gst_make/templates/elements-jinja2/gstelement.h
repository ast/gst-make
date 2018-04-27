{% extends "gstobject.h" %}

{% set GstClassName = "GstElement" %}

{% block includes %}
#include <gst/gst.h>
{% endblock %}

{% block instance_members %}
  GstPad *sinkpad;
  GstPad *srcpad;
{% endblock %}
