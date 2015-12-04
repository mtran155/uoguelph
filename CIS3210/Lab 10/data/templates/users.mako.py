# -*- encoding:utf-8 -*-
from mako import runtime, filters, cache
UNDEFINED = runtime.UNDEFINED
__M_dict_builtin = dict
__M_locals_builtin = locals
_magic_number = 8
_modified_time = 1412974678.219471
_enable_loop = True
_template_filename = '/home/undergrad/3/mtran04/CIS3210/Lab2/lab2/templates/users.mako'
_template_uri = 'users.mako'
_source_encoding = 'utf-8'
from webhelpers.html import escape
_exports = []


def render_body(context,**pageargs):
    __M_caller = context.caller_stack._push_frame()
    try:
        __M_locals = __M_dict_builtin(pageargs=pageargs)
        c = context.get('c', UNDEFINED)
        __M_writer = context.writer()
        # SOURCE LINE 1
        __M_writer(u'<!DOCTYPE html>\n<html lang="en">\n  <body>\n\t<div class="row" id="authenticated">\n\t<h1 style = "font-family:Serif">Welcome ')
        # SOURCE LINE 5
        __M_writer(escape(c.userName))
        __M_writer(u'! You are logged in!</h1>\n\t<br>\n\t<button type="button" class="btn btn-default" id="Logout">Logout</button>\n\t</div>\n  </body>\n\n<script src="js/jquery-1.11.1.js"></script>\n<script src="js/functions.js"></script>\n\n\n</html>\n\n')
        return ''
    finally:
        context.caller_stack._pop_frame()


