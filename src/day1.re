let captchaCheck = seq => {
  let rec aux = (seq, head, acc) =>
    switch seq {
    | [] => acc
    | [hd1, hd2, ...rest] =>
      hd1 === hd2 ?
        aux([hd2, ...rest], head, acc + hd1) : aux([hd2, ...rest], head, acc)
    | [hd] => hd === head ? aux([], head, acc + hd) : aux([], head, acc)
    };
  aux(seq, List.hd(seq), 0);
};

[@bs.send] external split : (string, string) => array(string) = "";

let parseInput = input => {
  let arr = split(input, "");
  Js.log(Array.to_list(arr));
  Js.log(arr);
  List.map(int_of_string, Array.to_list(arr));
};

let processInput = input => input |> parseInput |> captchaCheck;

let tests = ["1122", "1111", "1234", "91212129"];

let expected = [3, 4, 0, 9];

Js.log(List.map(processInput, tests));