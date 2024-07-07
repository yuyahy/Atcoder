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
        N: usize, X: usize,
        A: [usize; N],
    }
    // 考察メモ
    let sum: usize = A
        .iter()
        .enumerate()
        .map(|(index, &value)| {
            if (index + 1) % 2 == 0 {
                value - 1
            } else {
                value
            }
        })
        .sum();
    //println!("{}", sum);
    let result = if X >= sum { "Yes" } else { "No" };
    println!("{}", result);
}
