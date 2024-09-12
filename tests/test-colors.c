#include <libtest.h>
#include <lambdas.h>
#include <ui.h>

start_test(hex_color)
    color_t color;

    color = hex_color(0xA1B2C4D4);
    assert_pro(0xA1, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xB2, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xC4, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xD4, color.a, l_eq, l_hex_fmt, l_hex_fmt);

    color = hex_color(0xA1B2C4);
    assert_pro(0xA1, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xB2, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xC4, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xFF, color.a, l_eq, l_hex_fmt, l_hex_fmt);

    color = hex_color(0xA1B2);
    assert_pro(0xAA, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0x11, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xBB, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0x22, color.a, l_eq, l_hex_fmt, l_hex_fmt);

    color = hex_color(0xA1B);
    assert_pro(0xAA, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0x11, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xBB, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xFF, color.a, l_eq, l_hex_fmt, l_hex_fmt);

    color = hex_color(0xA1);
    assert_pro(0xA1, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xA1, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xA1, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xA1, color.a, l_eq, l_hex_fmt, l_hex_fmt);

    color = hex_color(0xA);
    assert_pro(0xAA, color.r, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xAA, color.g, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xAA, color.b, l_eq, l_hex_fmt, l_hex_fmt);
    assert_pro(0xAA, color.a, l_eq, l_hex_fmt, l_hex_fmt);

end_test

void color_test_init(void) {
    register_test(make_test_t(color, hex_color));
}
