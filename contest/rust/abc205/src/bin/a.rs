#[allow(unused_imports)]
use itertools::{iproduct, Itertools};
#[allow(unused_imports)]
use num_traits::pow;
#[allow(unused_imports)]
use proconio::{
    fastout, input,
    marker::{Chars, Usize1},
};
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashMap, HashSet, VecDeque};
#[allow(unused_imports)]
use std::iter::FromIterator;

#[allow(non_snake_case)]
#[fastout]
fn main() {
    input! {
        A: f64, B: f64,
    }

    let result = A * B / 100.0;
    if result.fract() == 0.0 {
        println!("{:?}", result as i64);
    } else {
        println!("{:?}", result);
    }
}
