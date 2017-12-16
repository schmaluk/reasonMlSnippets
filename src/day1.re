type gender =
  | Male
  | Female;

type student = {
  name: string,
  age: int,
  gender
};

let check = student =>
  switch student.gender {
  | Female => Js.log("Halle Frau " ++ student.name)
  | Male => Js.log("Halle Mann " ++ student.name)
  };

let max = {name: "Max", gender: Male, age: 33};

check(max);