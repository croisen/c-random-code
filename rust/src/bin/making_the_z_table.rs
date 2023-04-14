use core::mem::MaybeUninit;
use std::f64::consts::PI;
use std::f64::consts::E;
use std::ffi::CString;
// use std::ptr::null;
use gmp_mpfr_sys::mpfr;
use gmp_mpfr_sys::mpfr::mpfr_t;
use gmp_mpfr_sys::mpfr::rnd_t::RNDD;

unsafe fn natural_pdf(rop: *mut mpfr_t, x: *mut mpfr_t) -> () {
    let mut __z = MaybeUninit::uninit();
    let mut __e = MaybeUninit::uninit();
    let mut _pi = MaybeUninit::uninit();

    // mpfr::inits2(512, __z.as_mut_ptr(), __e.as_mut_ptr(), _pi.as_mut_ptr(), null as mpfr::mpfr_ptr);
    // Hmmmm I need mpfr_ptr to null but it is private
    mpfr::init2(__e.as_mut_ptr(), 2);
    mpfr::init2(__z.as_mut_ptr(), 2);
    mpfr::init2(_pi.as_mut_ptr(), 2);

    let mut __z = __z.assume_init();
    let mut __e = __e.assume_init();
    let mut _pi = _pi.assume_init();
    
    mpfr::pow_ui(&mut __z, x, 2, RNDD);
    mpfr::div_ui(&mut __z, &__z, 2, RNDD);
    mpfr::neg(&mut __z, &__z, RNDD);
    mpfr::set_d(&mut __e, E, RNDD);
    mpfr::set_d(&mut _pi, PI, RNDD);
    mpfr::pow(&mut __z, &__e, &__z, RNDD);
    mpfr::mul(&mut _pi, &_pi, &_pi, RNDD);
    mpfr::sqrt(&mut _pi, &_pi, RNDD);
    mpfr::div(rop, &__z, &_pi, RNDD);
    // mpfr::clears(&mut __z, &mut __e, &mut _pi); I need mpfr_ptr to null for this too
    mpfr::clear(&mut __z);
    mpfr::clear(&mut __e);
    mpfr::clear(&mut _pi);
}

fn main() {
    unsafe {
        let mut x = MaybeUninit::uninit();
        let mut rop = MaybeUninit::uninit();
        mpfr::init_set_d(x.as_mut_ptr(), 0.00, RNDD);
        mpfr::init2(rop.as_mut_ptr(), 2);
        let mut x = x.assume_init();
        let mut rop = rop.assume_init();
        let mut rop = natural_pdf(&mut rop, &mut x);
        let c_str = CString::new("%5.RNF\n").unwrap();
        mpfr::printf(c_str.as_ptr() as *const i8, &mut rop);
    }
}
