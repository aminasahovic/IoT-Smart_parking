const firebaseConfig = {
  apiKey: "AIzaSyBUZwzkXHfUGssV9CGcDbG7TPQucNYvyjY",
  authDomain: "amina-iot.firebaseapp.com",
  databaseURL: "https://amina-iot-default-rtdb.firebaseio.com",
  projectId: "amina-iot",
  storageBucket: "amina-iot.appspot.com",
  messagingSenderId: "907528157535",
  appId: "1:907528157535:web:2c74f5b8d87b585553deea",
  measurementId: "G-ZW3213C5B5",
};
firebase.initializeApp(firebaseConfig);
firebase.analytics();
let showRezervacija = true;
let showInfo = false;
let show;
function reset() {
  document.getElementById("pleace").style.backgroundColor = "#2D2D2D";
  document.getElementById("info").style.backgroundColor = "#2D2D2D";
  document.getElementById("options").style.backgroundColor = "#2D2D2D";
  document.getElementById("pleace").style.color = "whitesmoke";
  document.getElementById("info").style.color = "whitesmoke";
  document.getElementById("options").style.color = "whitesmoke";
  document.getElementsByClassName("info_div")[0].style.display = "none";
  document.getElementsByClassName("pleace_button")[0].style.display = "none";
  document.getElementsByClassName("options_button")[0].style.display = "none";
}
function setColor(element) {
  element.style.backgroundColor = "#F6D139";
  element.style.color = "#414141";
}
function onPleace(element) {
  reset();
  setColor(element);
  document.getElementsByClassName("pleace_button")[0].style.display = "block";
}
function onInfo(element) {
  reset();
  setColor(element);
  document.getElementsByClassName("info_div")[0].style.display = "block";
}
function onload() {
  element = document.getElementById("pleace_button");
  setColor(element);
  document.getElementsByClassName("pleace_button")[0].style.display = "block";
}
function onOptions(element) {
  reset();
  setColor(element);
  document.getElementsByClassName("options_button")[0].style.display = "block";
}
let zauzeto = false; //firebase nastavi
if (zauzeto) {
  let myButton = document.getElementById("parkingMjesto");
  myButton.disabled = true;
  myButton.style.backgroundColor = "#2D2D2D";
  myButton.style.border = "1px solid whitesmoke";
  document.getElementById("status").innerText = "Zauzeto";
}
let rezervisano = false;
setInterval(function () {
  const ref = database1.ref("BrojSlobodnih");
  ref.once("value", function (snapshot) {
    let brojMjesta = snapshot.val();
    if (brojMjesta == 0) {
      let myButton = document.getElementById("parkingMjesto");
      document.getElementById("status").innerText = "Slobodno";
      myButton.style.backgroundColor = "rgb(154, 135, 135)";
      rezervisano = false;
    }
  });
}, 2000);

function onReservisi() {
  var firebaseRef = firebase.database().ref("BrojSlobodnih");
  let myButton = document.getElementById("parkingMjesto");
  if (rezervisano == true) {
    document.getElementById("status").innerText = "Slobodno";
    alert("Otkazali ste rezervaciju!");
    firebaseRef.set(0);
    myButton.style.backgroundColor = "rgb(154, 135, 135)";
    rezervisano = false;
  } else {
    firebaseRef.set(1);
    rezervisano = true;
    myButton.style.backgroundColor = "#7DC242";
    document.getElementById("status").innerText = "Rezervisano";
    alert("Uspjesno rezervisano mjesto");
  }
}
function rampa() {
  if (rezervisano == true) {
    var rampa = firebase.database().ref("rampa");
    rampa.set(true);
    console.log("Otvori rampu");
    let myButton = document.getElementById("parkingMjesto");
    myButton.style.backgroundColor = "#2D2D2D";
    myButton.style.border = "1px solid whitesmoke";
    document.getElementById("status").innerText = "Zauzeto";
  } else {
    alert("Ne možete možete otvoriti rampu, parking je zauzet");
  }
}

let timeEntry = document.getElementById("timeEntry");
let timeExit = document.getElementById("timeExit");
let timeDatabase1;
let timeDatabase2;
const database1 = firebase.database();

setInterval(function () {
  const ref = database1.ref("VrijemeUlaska1");
  ref.once("value", function (snapshot) {
    timeEntry.innerText = snapshot.val();
  });
}, 2000);

setInterval(function () {
  const ref = database1.ref("VrijemeIzlaska1");
  ref.once("value", function (snapshot) {
    timeExit.innerText = snapshot.val();
  });
}, 2000);
