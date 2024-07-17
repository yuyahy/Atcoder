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

fn is_next_number(x: char, y: char) -> bool {
    let x = x as u8 - '0' as u8;
    let y = y as u8 - '0' as u8;

    let range = 0..=8;

    // println!("x = {}, y = {}", x, y);

    if range.contains(&x) {
        // println!("result : {}", y == x + 1);
        return y == x + 1;
    } else {
        // println!("result : {}", y == 0);
        return y == 0;
    }
}
fn main() {
    input! {
        s: Chars,
    }
    // 考察メモ
    // println!("{:?}", s);
    let char_digit = '5';

    if s.iter().all(|x| *x == s[0]) {
        println!("Weak");
    } else {
        // assert!(is_next_number('0', '1'));
        // assert!(!is_next_number('1', '0'));
        // assert!(is_next_number('9', '0'));

        // if s.windows(2).all(|window| {
        //     is_next_number(window[0], window[1])
        // }) {
        if s.iter().tuple_windows().all(|(prev, next)| {
            is_next_number(*prev, *next)
        }) {
            println!("Weak");
        } else {
            println!("Strong");
        }
    }
}
