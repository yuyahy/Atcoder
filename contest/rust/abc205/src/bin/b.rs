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

#[fastout]
fn main() {
    input! {
        N: usize,
        mut A: [usize; N],
    }
    A.sort();

    // for window in A.windows(2) {
    for (prev, next) in A.iter().tuple_windows() {
        // let (prev, next) = (window[0], window[1]);
        if prev >= next {
            println!("No");
            return;
        }
    }
    println!("Yes");
}
