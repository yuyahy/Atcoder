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
        A: usize, B: usize,
    }

    // A回サイコロを振ったときにとりうる目の範囲は[1*A, 6*A]
    let range = A..=6 * A;
    let result =
        if range.contains(&B) { "Yes" } else { "No" };

    println!("{}", result);
}
