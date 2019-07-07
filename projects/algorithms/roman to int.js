$_$wp(1);
var $_$wvd1 = $_$w(1, 0), romanToInt = function (s) {
        $_$wf(1);
        let a = ($_$w(1, 1), {
            I: 1,
            V: 5,
            X: 10,
            L: 50,
            C: 100,
            D: 500,
            M: 1000
        });
        let n = ($_$w(1, 2), 0), c = 0, p = 0;
        for (let i = s.length - 1; $_$w(1, 3), i >= 0; --i) {
            $_$w(1, 4), c = a[s[i]];
            if ($_$w(1, 5), c < p) {
                $_$w(1, 6), n -= c;
            } else {
                $_$w(1, 7), p = c;
                $_$w(1, 8), n += c;
            }
        }
        return $_$w(1, 9), n;
    };
$_$w(1, 10), $_$tracer.log(romanToInt('IV'), 'romanToInt(\'IV\')', 1, 10);
$_$wpe(1);