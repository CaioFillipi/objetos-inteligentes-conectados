function goToOtherPage(){
    var user = document.getElementById("user");
    var pass = document.getElementById("pwd");

    if(user.value == "user&2023!" && pass.value == "@+-b24ac"){
        window.location.href = "./panel.html";
        return;
    }

    alert("Usuário e/ou senha incorretos!")
}