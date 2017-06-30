import requests
import json
import sys

client_id = 'mobile-services-id'
client_secret = 'segredo' #aqui sua client_secret
login = sys.argv[1]
username = login #aqui seu username
password = login #aqui seu password
turma_id = '57596654'

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
print token
#montamos a url de projetos injetando o token como parametro
#URL_Projetos = URL_BASE+ 'ensino-services/services/consulta/frequenciadiadocente/usuario/{0}/{1}?access_token={2}'.format(turma_id, 1498867199000, token)
URL_Projetos = URL_BASE+ 'ensino-services/services/consulta/frequenciadiadocente/usuario/{0}/{1}?access_token={2}'.format(turma_id, 1496977200000, token)
#agora como exemplo fazemos uma requisicao aos projetos de pesquisa com o token obtido
requisicao_projetos = requests.get(URL_Projetos)

#convertemos a resposta para json
frequencia = json.loads(requisicao_projetos.content)
frequencia['status'] = 1
frequencia['dataLong'] = 1496447999000
frequencia['sincronizado'] = 1
del frequencia['data']

#imprimimos o resultado da api de projetos, e possivel acessar campos em especifico com 'resposta['campo_que_deseja']'
#print json.dumps(frequencia, indent=2, sort_keys=True)
#print projetos

for element in frequencia['frequencias']:
	element['faltas'] = 2

file = open('presentes.txt', 'r')
for aluno_id in file:
	for element in frequencia['frequencias']:
		if element['idDiscente'] == int(aluno_id):
			element['faltas'] = 0

#imprimimos o resultado da api de projetos, e possivel acessar campos em especifico com 'resposta['campo_que_deseja']'
print json.dumps(frequencia, indent=2, sort_keys=True)

URL_Projetos = 'http://apitestes2.info.ufrn.br/ensino-services/services/consulta/frequenciadiadocente?access_token={0}'.format(token)
#agora como exemplo fazemos uma requisicao aos projetos de pesquisa com o token obtido
headers = {'Content-type': 'application/json', 'Authorization' : 'Bearer ' + token}
requisicao_projetos = requests.post(URL_Projetos,data=json.dumps(frequencia), headers=headers)
print requisicao_projetos.status_code