<img src="https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B"/>
<img src="https://img.shields.io/badge/HTML-239120?style=for-the-badge&logo=html5&logoColor=white"/>
<img src="https://img.shields.io/badge/CSS-239120?&style=for-the-badge&logo=css3&logoColor=white"/>
<img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black"/>
<img src="https://img.shields.io/static/v1?label=git&message=SCM&color=black&style=for-the-badge&logo=git"/>
<h1>Alimentador de Peixes Automático</h1>

Projeto desenvolvido para a disciplina de Objetos Inteligentes Conectados. O projeto desenvolvido foi um alimentador de peixes automático, com a utilização da plataforma Arduino.

Materiais utilizados para desenvolver o projeto:
<ul>
  <li>
    <a target="_blank" href="https://store-usa.arduino.cc/products/arduino-uno-rev3">Arduino Uno;</a>
  </li>
  <li>
    <a target="_blank" href="https://www.embarcados.com.br/wp-content/uploads/2018/01/projeto-iot-portatil-850x510.png">Node MCU;</a>
  </li>
  <li>
    <a target="_blank" href="https://cdn.awsli.com.br/600x700/804/804388/produto/204877418/driver-motor-ponte-h-dupla-l298-motor-passo-ou-dc-1-mkcyqx.jpg">Driver Ponte H;</a>
  </li>
  <li>
    <a target="_blank" href="https://cdn.awsli.com.br/600x700/468/468162/produto/19414386ea97456c0c.jpg">Placa Protoboard 400 pontos;</a>
  </li>
  <li>
    <a target="_blank" href="https://cdn.awsli.com.br/600x700/980/980586/produto/181175637/9b64b30c23.jpg">Mini Motor DC;</a>
  </li>
  <li>
    <a target="_blank" href="https://http2.mlstatic.com/D_NQ_NP_987254-MLB46742289443_072021-W.jpg">Porta Pilhas 4 Pilhas;</a>
  </li>
  <li>
    <a target="_blank" href="https://www.huinfinito.com.br/1490-large_default/sensor-de-temperatura-ds18b20-prova-d-agua.jpg">Sensor de Temperatura DS18B20;</a>
  </li>
  <li>
    <a target="_blank" href="https://http2.mlstatic.com/D_NQ_NP_821808-MLB46512363443_062021-O.webp">Push Button.</a>
  </li>
</ul>

Abaixo está o esquema para a montagem do projeto.

Esquema de montagem para o dispositivo que irá alimentar os peixes por meio do motor DC.

![image](https://github.com/CaioFillipi/objetos-inteligentes-conectados/assets/19175715/42b7bada-8c11-4478-97cd-2cddbf539e8d)


Esquema do dispositivo secundário que permite a ativação remota utilizando o protocolo MQTT.
![image](https://github.com/CaioFillipi/objetos-inteligentes-conectados/assets/19175715/2394d16a-b424-47d7-b0e4-68cdcd2526c9)

Antes de realizar o upload do projeto para o arduino é necessário realizar a instalação antes. Basta acessar ao site <a href="https://www.arduino.cc/en/software">Arduino IDE</a> e realizar o donwload da IDE. Após instalar a IDE,
basta realizar o clone deste repositório. Nele existem 3 projetos, o projeto responsavél pelo alimentador é o Consumer_MQTT, basta realizar o Upload dele para o NodeMCU. O projeto Publisher_MQTT,
deverá ser inserido no NodeMCU do dispositivo secundário. Em ambos os projetos será necessário realizar algumas modificações.

Em ambos os projetos será necessário alterar os valores das variavéis SSID e PASSWORD, que correspondem ao nome da rede Wifi e Senha respectivamente.

![image](https://github.com/CaioFillipi/objetos-inteligentes-conectados/assets/19175715/d3c09ab9-1614-45a2-a02b-e5f6d4288327)

Outro ponto importante em relação ao projeto Consumer_MQTT é em relação ao Sensor de Temperatura. Ele utiliza duas bibliotecas que não vem instaladas por padrão na IDE do Arduino, são elas
<strong>DallasTemperature</strong> e <strong>OneWire</strong>. Segue um passo-a-passo de como realizar a instalação <a href="https://curtocircuito.com.br/blog/Categoria%20Arduino/como-utilizar-o-ds18b20">
Instalação Bibliotecas</a>.

O projeto também dispõe de um portal na qual é possível realizar o acionamento do motor. Para realizar a comunicação do portal com o Broker utilizei a biblioteca 
<a href="https://github.com/mqttjs/MQTT.js">MQTT.js</a>

Tela de login do portal.

![image](https://github.com/CaioFillipi/objetos-inteligentes-conectados/assets/19175715/4787bd48-c9b2-44b4-92aa-f1843f450138)

Painel de controle do alimentador

![image](https://github.com/CaioFillipi/objetos-inteligentes-conectados/assets/19175715/095da4e7-c3b5-49ba-bff5-671915fe9cce)


Após todas bibliotecas instaladas, basta realizar o upload dos projetos para as placas e aproveitar!
