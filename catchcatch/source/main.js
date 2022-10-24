import "./CSS/UI/upgrade.css";
import "./CSS/UI/index.css";
import "./CSS/GAME/style.css";
// import initUpgrade from "./JS/upgrade";
import StartPageInit from "./JS/UI/StartPage.js";
import CharPageInit from "./JS/UI/CharSpace";

// localStorage.clear();

// 로컬 데이터
global.LocalData = localStorage.getItem("data");
if (global.LocalData === null) {
  localStorage.setItem(
    "data",
    JSON.stringify({ Coin: 1000, Cat: [false, false, false, false, false] })
  );
}
global.LocalData = JSON.parse(localStorage.getItem("data"));

// 게임 시작 전 데이터
global.ChoiceCat = -1;
global.ChoiceLevel = 0;

function Init() {
  StartPageInit(); //스타트 페이지 init
  CharPageInit(); // 캐릭터 페이지 init
}

function SaveData() {
  localStorage.setItem("data", JSON.stringify(LocalData));
}
export { SaveData };

Init();
