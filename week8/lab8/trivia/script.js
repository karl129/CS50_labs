const LIGHT_GREEN = "#4CAF50", LIGHT_RED = "#F44336";

// 保存正确答案
const correctAnswer = "Beijing";

const buttons = document.querySelectorAll("button.ans");
let question1 = document.querySelector("#q1")
let question2 = document.querySelector("#q2")

// 恢复颜色
function resetColor(buttons){
    const buttonArray = Array.from(buttons);

    buttonArray.forEach(button =>{
        button.style.backgroundColor = "#d9edff";
    })
}

// 删除提示
function deletHint(q){
    let message = document.querySelector(q)
    if (message){
        message.parentNode.removeChild(message);
    }
}

buttons.forEach(button => {
    button.addEventListener("click", () => {
        deletHint("#q1 p");
        resetColor(buttons);
        if (button.innerText == correctAnswer) {
            button.style.backgroundColor = LIGHT_GREEN;
            question1.insertAdjacentHTML("beforeend", "<p>Correct!</p>");
        } else {
            button.style.backgroundColor = LIGHT_RED;
            question1.insertAdjacentHTML("beforeend", "<p>Incorrect!</p>");
        }
    })
})
const freeAns = "cs50"
const free_button = document.querySelector("#free_ans");
free_button.addEventListener("click", () => {
    deletHint("#q2 p");
    const usr_input = document.querySelector("input");
    if (usr_input.value == freeAns){
        console.log("correct!")
        usr_input.style.backgroundColor = LIGHT_GREEN;
        question2.insertAdjacentHTML("beforeend", "<p>Correct!</p>");
    } else {
        console.log("wrong!")
        usr_input.style.backgroundColor = LIGHT_RED;
        question2.insertAdjacentHTML("beforeend", "<p>Incorrect!</p>");
    }
})
