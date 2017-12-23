/* Links: https://reasonml.github.io/guide/language/object */
/*
  *
   Plain Js-Objects in Reason:
   - type: Js.t('a) where 'a is the Reason-type
   - fields accessible via ##
   - represent/compiled to plain JS-objects
   - any methods and fields of Js.t('a)-objects are accessible via ##-operator
 */
[%%bs.raw
  {| const jsObject = {
      myName: "blabla",
      myMethod: (greeting) => console.log(`${greeting}, Mr.${jsObject.myName}`)
    };|}
];

[@bs.val] external jsObject : Js.t('a) = "jsObject";

/* The type Js.t('a) doesnt provide any field or method information: */
/* Any field is accessible: */
Js.log(jsObject##myName);

/* Any method is accessible: */
jsObject##myMethod("Hello");
/*
 *
 Providng type information on JS-Objects:
 *
 */