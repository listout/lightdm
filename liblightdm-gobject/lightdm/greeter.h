/*
 * Copyright (C) 2010 Robert Ancell.
 * Author: Robert Ancell <robert.ancell@canonical.com>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option) any
 * later version. See http://www.gnu.org/copyleft/lgpl.html the full text of the
 * license.
 */

#ifndef _LIGHTDM_GREETER_H_
#define _LIGHTDM_GREETER_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define LIGHTDM_TYPE_GREETER            (lightdm_greeter_get_type())
#define LIGHTDM_GREETER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), LIGHTDM_TYPE_GREETER, LightDMGreeter));
#define LIGHTDM_GREETER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), LIGHTDM_TYPE_GREETER, LightDMGreeterClass))
#define LIGHTDM_IS_GREETER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LIGHTDM_TYPE_GREETER))
#define LIGHTDM_IS_GREETER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), LIGHTDM_TYPE_GREETER))
#define LIGHTDM_GREETER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), LIGHTDM_TYPE_GREETER, LightDMGreeterClass))

typedef struct _LightDMGreeter        LightDMGreeter;
typedef struct _LightDMGreeterClass   LightDMGreeterClass;

#include "user.h"
#include "language.h"
#include "layout.h"
#include "session.h"

/**
 * LightDMPromptType:
 * @LIGHTDM_PROMPT_TYPE_QUESTION: Prompt is a question.  The information can be shown as it is entered.
 * @LIGHTDM_PROMPT_TYPE_SECRET: Prompt is for secret information.  The entered information should be obscured so it can't be publically visible.
 */
typedef enum
{
    LIGHTDM_PROMPT_TYPE_QUESTION,
    LIGHTDM_PROMPT_TYPE_SECRET
} LightDMPromptType;

/**
 * LightDMMessageType:
 * @LIGHTDM_MESSAGE_TYPE_INFO: Informational message.
 * @LIGHTDM_MESSAGE_TYPE_ERROR: Error message.
 */
typedef enum
{
    LIGHTDM_MESSAGE_TYPE_INFO,
    LIGHTDM_MESSAGE_TYPE_ERROR
} LightDMMessageType;

struct _LightDMGreeter
{
    GObject parent_instance;
};

struct _LightDMGreeterClass
{
    GObjectClass parent_class;

    void (*connected)(LightDMGreeter *greeter);
    void (*show_prompt)(LightDMGreeter *greeter, const gchar *text, LightDMPromptType type);
    void (*show_message)(LightDMGreeter *greeter, const gchar *text, LightDMMessageType type);
    void (*authentication_complete)(LightDMGreeter *greeter);
    void (*session_failed)(LightDMGreeter *greeter);
    void (*autologin_timer_expired)(LightDMGreeter *greeter);
    void (*user_added)(LightDMGreeter *greeter, LightDMUser *user);
    void (*user_changed)(LightDMGreeter *greeter, LightDMUser *user);
    void (*user_removed)(LightDMGreeter *greeter, LightDMUser *user);
    void (*quit)(LightDMGreeter *greeter);
};

GType lightdm_greeter_get_type (void);

LightDMGreeter *lightdm_greeter_new (void);

gboolean lightdm_greeter_connect_to_server (LightDMGreeter *greeter);

const gchar *lightdm_greeter_get_hostname (LightDMGreeter *greeter);

gint lightdm_greeter_get_num_users (LightDMGreeter *greeter);

GList *lightdm_greeter_get_users (LightDMGreeter *greeter);

LightDMUser *lightdm_greeter_get_user_by_name (LightDMGreeter *greeter, const gchar *username);

const gchar *lightdm_greeter_get_default_language (LightDMGreeter *greeter);

GList *lightdm_greeter_get_languages (LightDMGreeter *greeter);

GList *lightdm_greeter_get_layouts (LightDMGreeter *greeter);

void lightdm_greeter_set_layout (LightDMGreeter *greeter, const gchar *layout);

const gchar *lightdm_greeter_get_layout (LightDMGreeter *greeter);

GList *lightdm_greeter_get_sessions (LightDMGreeter *greeter);

const gchar *lightdm_greeter_get_hint (LightDMGreeter *greeter, const gchar *name);

const gchar *lightdm_greeter_get_default_session_hint (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_hide_users_hint (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_has_guest_account_hint (LightDMGreeter *greeter);

const gchar *lightdm_greeter_get_select_user_hint (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_select_guest_hint (LightDMGreeter *greeter);

const gchar *lightdm_greeter_get_autologin_user_hint (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_autologin_guest_hint (LightDMGreeter *greeter);

gint lightdm_greeter_get_autologin_timeout_hint (LightDMGreeter *greeter);

void lightdm_greeter_cancel_timed_login (LightDMGreeter *greeter);

void lightdm_greeter_login (LightDMGreeter *greeter, const char *username);

void lightdm_greeter_login_with_user_prompt (LightDMGreeter *greeter);

void lightdm_greeter_login_as_guest (LightDMGreeter *greeter);

void lightdm_greeter_respond (LightDMGreeter *greeter, const gchar *response);

void lightdm_greeter_cancel_authentication (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_in_authentication (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_is_authenticated (LightDMGreeter *greeter);

const gchar *lightdm_greeter_get_authentication_user (LightDMGreeter *greeter);

void lightdm_greeter_start_session (LightDMGreeter *greeter, const gchar *session);

void lightdm_greeter_start_default_session (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_can_suspend (LightDMGreeter *greeter);

void lightdm_greeter_suspend (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_can_hibernate (LightDMGreeter *greeter);

void lightdm_greeter_hibernate (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_can_restart (LightDMGreeter *greeter);

void lightdm_greeter_restart (LightDMGreeter *greeter);

gboolean lightdm_greeter_get_can_shutdown (LightDMGreeter *greeter);

void lightdm_greeter_shutdown (LightDMGreeter *greeter);

G_END_DECLS

#endif /* _LIGHTDM_GREETER_H_ */
