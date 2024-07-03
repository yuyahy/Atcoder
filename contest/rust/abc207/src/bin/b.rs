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
        A: usize, B: usize, C: usize, D: usize,
    }

    // if B > C {
    //     println!("-1");
    //     return;
    // }

    let mut cnt: u32 = 0;
    let mut current_red = 0;
    let mut current_blue = A;

    let x: u32 = 8;
    let result = 10u32.pow(x);
    while true {
        if current_blue <= current_red * D {
            println!("{}", cnt);
            return;
        }
        current_blue += B;
        current_red += C;
        cnt += 1;
        if cnt > result - 1 {
            break;
        }
    }
    println!("-1");
}
