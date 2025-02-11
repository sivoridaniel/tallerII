/*
 * AbmUserService.h
 *
 *  Created on: 13 de abr. de 2016
 *      Author: pablo
 */

#ifndef SRC_SERVICE_ABMUSERSERVICE_H_
#define SRC_SERVICE_ABMUSERSERVICE_H_

#include "../../dao/UserDao.h"
#include "../../dao/MatchDao.h"
#include "../../dao/SearchStatsDao.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "RemoteSharedService.h"
#include "../api/IAbmUserService.h"
#include <string>

using namespace std;
using namespace log4cplus;

/**
 * Clase que se utiliza para el ABM de usuarios en el server. Basicamente es
 * para poder almacenar los tokens para poder controlar la sesion del usuario.
 */
class AbmUserService: public IAbmUserService
{
private:
	UserDao* userDao;
	MatchDao* matchDao;
	SearchStatsDao* searchStatsDao;
	IRemote* remoteSharedService;

	void existeUsuario(string email);

public:
	AbmUserService(string url);

	AbmUserService(UserDao* userDao, MatchDao* matchDao, SearchStatsDao* searchStatsDao, IRemote* sharedServer);

	/**
	 * Crea un nuevo usuario con password, token y email para un posible recupero
	 * de cuenta.
	 *
	 * @param string name
	 * @param string password
	 * @param string token
	 * @param string email
	 */
	string createNewUser(UserProfile* userProfile);
	/**
	 * Modificación del usuario. Puede modificar su password, mail y cualquier otro
	 * tipo de contenido relacionado con su perfil.
	 *
	 * Se disparará una excepción que puede ser MergeDbException en caso de no poder
	 * actualizar las credenciales.
	 *
	 * @param userProfile
	 * @throw MergeDbException,JsonParseException
	 */
	void modifyUser(UserProfile* userProfile);

	/**
	 * Actualización del token.
	 *
	 * @param userProfile
	 */
	void updateToken(UserProfile* userProfile);

	/**
	 * Obtiene la lista de intereses
	 *
	 * @return list<Interest*> lista de intereses
	 */
	list<Interest*> getInterests();

	/**
	 * Obtiene la foto del usuario
	 *
	 * @param id
	 * @return string photo en base 64
	 */
	string getPhoto(string id);

	virtual ~AbmUserService();
};

#endif /* SRC_SERVICE_ABMUSERSERVICE_H_ */
