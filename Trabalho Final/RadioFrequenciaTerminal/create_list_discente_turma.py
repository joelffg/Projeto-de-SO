import requests
import json
import sys

client_id = 'mobile-services-id'
client_secret = 'segredo' #aqui sua client_secret
username = sys.argv[1] #aqui seu username
password = sys.argv[2] #aqui seu password
turma_id = sys.argv[3]

#url da api
URL_BASE = 'http://apitestes.info.ufrn.br/'

#montamos a url de login injetando os parametros definidos no inicio do codigo
url_token = URL_BASE + 'authz-server/oauth/token?client_id={0}&client_secret={1}&username={2}&password={3}&grant_type=password'.format(client_id, client_secret, username, password)

# efetuamos uma requisicao a api passando a url_projetos
requisicao_token = requests.post(url_token)

# convertemos o resultado em json para um acesso mais facil aos dados
resposta = json.loads(requisicao_token.content)

# imprimimos o resultado da api, e possivel acessar campos em especifico com 'resposta['campo_que_deseja']'
# print resposta

#salvamos o token em uma variavel pra usar em um exemplo de chamada a api
token = resposta['access_token']

#montamos a url de projetos injetando o token como parametro
URL_Projetos = URL_BASE+ 'ensino-services/services/consulta/listaparticipantesturma/usuario/{0}?access_token={1}'.format(turma_id, token)

#agora como exemplo fazemos uma requisicao aos projetos de pesquisa com o token obtido
requisicao_turma = requests.get(URL_Projetos)

#convertemos a resposta para json
turma = json.loads(requisicao_turma.content)
discentes = turma['discentes']
# print discentes

file = open('nome_id_discente.txt', 'w')
for element in discentes:
	file.write(element['nome'].encode('utf-8') + '\n')
	file.write(str(element['id']) + '\n')
file.close