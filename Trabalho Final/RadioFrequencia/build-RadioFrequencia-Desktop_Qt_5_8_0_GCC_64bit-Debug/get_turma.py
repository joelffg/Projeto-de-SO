import requests
import json
import sys

client_id = 'mobile-services-id'
client_secret = 'segredo' #aqui sua client_secret
username = sys.argv[1] #aqui seu username
password = sys.argv[2] #aqui seu password
turma_id = '57596654'

#url da api
URL_BASE = 'https://apitestes.info.ufrn.br/'

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
URL_Projetos = URL_BASE+ 'ensino-services/services/consulta/turmas/usuario/docente?access_token={0}'.format(token)

#agora como exemplo fazemos uma requisicao aos projetos de pesquisa com o token obtido
headers = {'Content-type': 'application/json; charset=utf-8'}
requisicao_turma = requests.get(URL_Projetos)
#print requisicao_projetos.status_code
#convertemos a resposta para json
turmas = json.loads(requisicao_turma.content)
# print json.dumps(turmas, indent=2, sort_keys=True)
#imprimimos o resultado da api de projetos, e possivel acessar campos em especifico com 'resposta['campo_que_deseja']'

file = open('turmas_docente.txt', 'w')
for element in turmas:
	file.write(element['descricaoCompleta'].encode('utf-8') + '\n')
	file.write(str(element['id']) + '\n')
file.close

if(turmas != []):
	turmas = 200
print turmas
