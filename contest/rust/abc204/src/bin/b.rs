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
        A: [usize; N],
    }
    // println!("{:?}", A);
    let result: usize = A
        .iter()
        .filter(|&&x| x > 10)
        .map(|&x| x - 10)
        .sum();
    println!("{:?}", result);
}
