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
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef _{{r.GST_REPLACE}}_H_
#define _{{r.GST_REPLACE}}_H_

{% block includes %}{% endblock %}

G_BEGIN_DECLS

#define {{r.GST_TYPE_REPLACE}} ({{r.gst_replace}}_get_type())
#define {{r.GST_REPLACE}}(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),{{r.GST_TYPE_REPLACE}},{{r.GstReplace}}))
#define {{r.GST_REPLACE}}_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass),{{r.GST_TYPE_REPLACE}},{{r.GstReplace}}Class))
#define {{r.GST_IS_REPLACE}}(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),{{r.GST_TYPE_REPLACE}}))
#define {{r.GST_IS_REPLACE}}_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE((klass),{{r.GST_TYPE_REPLACE}}))

typedef struct _{{r.GstReplace}} {{r.GstReplace}};
typedef struct _{{r.GstReplace}}Class {{r.GstReplace}}Class;

struct _{{r.GstReplace}}
{
  {{GstClassName if GstClassName else "GstObject"}} base_{{r.replace}};
  {% block instance_members %}{% endblock %}
};

struct _{{r.GstReplace}}Class
{
  {{GstClassName if GstClassName else "GstObject"}}Class base_{{r.replace}}_class;
};

GType {{r.gst_replace}}_get_type (void);

G_END_DECLS

#endif
