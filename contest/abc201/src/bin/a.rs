#[allow(unused_imports)]
use itertools::{iproduct, Itertools};
use num::Integer;
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
        mut a:[i64;3],
    }
    a.sort();

    let result = if a[1] - a[0] == a[2] - a[1] {
        "Yes"
    } else {
        "No"
    };
    println!("{}", result);
}
