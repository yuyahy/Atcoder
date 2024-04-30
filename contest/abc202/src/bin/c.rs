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
        B: [usize; N],
        C: [usize; N],
    }
    // println!("{:?}", A);
    // println!("{:?}", B);
    // println!("{:?}", C);

    // <数値, 出現回数>のmap
    let mut number_counter = HashMap::<usize, usize>::new();
    for a in A {
        *number_counter.entry(a).or_insert(0) += 1;
    }

    // A.sort();
    // println!("{:?}", number_counter);

    let mut result = 0;
    for c in C {
        match number_counter.get(&B[c - 1]) {
            Some(&number) => result += number,
            _ => (),
        }
    }
    println!("{}", result);
}
