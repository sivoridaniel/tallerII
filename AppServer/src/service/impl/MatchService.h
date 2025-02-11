/*
 * MatchService.h
 *
 *  Created on: Apr 5, 2016
 *      Author: agustin
 */

#ifndef MATCHSERVICE_H_
#define MATCHSERVICE_H_

#include "../../dao/MatchDao.h"
#include "../../dao/SearchStatsDao.h"
#include "ChatService.h"
#include "RemoteSharedService.h"
#include "../../exception/IllegalStateException.h"
#include "../../exception/EntityExistsException.h"
#include "../api/IMatchService.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <string>

using namespace std;
using namespace log4cplus;

/**
 * Matcheo de usuario por intereses.
 */
class MatchService: public IMatchService
{
private:
	MatchDao* matchDao;
	SearchStatsDao* searchStatsDao;
	IChatService* chatService;
	IRemote* sharedService;

public:
	MatchService(string url);

	/**
	 * Constructor que se utiliza para poder ser utilizado con gmock.
	 * De esta manera podemos mockear el DAO para no realizar el llamado a
	 * la base de datos y poder realizar los test unit de los métodos de la
	 * clase.
	 *
	 * @param MatchDao
	 * @param SearchStatsDao
	 * @param chatService
	 * @param sharedService
	 */
	MatchService(MatchDao* matchDao, SearchStatsDao* searchStats, IChatService* chatService, IRemote* sharedService);

	virtual ~MatchService();
	/**
	 * Agrega a la lista de likes el usuario por el cual se tiene interes.
	 *
	 * En caso de no poder actualizarse la lista de likes se disparará la excepcion
	 * EntityExistsException o EntityNotFoundException.
	 *
	 *
	 * @param string idUser
	 * @param string idUserAccepted
	 * @throw EntityExistsException, EntityNotFoundException
	 * @return bool Si se pudo agregar el usuario a la lista de likes
	 */
	bool addToYesList(string idUser, string idUserAccepted);
	/**
	 * En caso de que el usuario rechace a alguno de la lista, se lo agregará
	 * a la lista de rechazados.
	 *
	 * En caso de no poder actualizarse la lista de rechazados se disparará la excepcion
	 * EntityExistsException o EntityNotFoundException.
	 *
	 * @param string idUser
	 * @param string idUserRejected
	 * @throw EntityExistsException, EntityNotFoundException
	 */
	void addToNoList(string idUser, string idUserRejected);
	/**
	 * Devuelve la lista de nuevos matches de un usuario.
	 * En caso de no poder realizar la operación disparará la excepción EntityNotFoundException.
	 *
	 * @param idUser
	 * @throw EntityNotFoundException
	 * @return list<UserProfile*> lista de nuevos matches
	 *
	 */
	list<UserProfile*> getNewMatches(string idUser);

	/**
	 * Devuelve la lista de nuevos chats de un usuario.
	 * En caso de no poder realizar la operación disparará la excepción EntityNotFoundException.
	 *
	 * @param idUser
	 * @throw EntityNotFoundException
	 * @return list<UserProfile*> lista de nuevos chats
	 *
	 */
	list<UserProfile*> getChats(string idUser);

	/**
	 * Valida que no sea el mismo usuario, que no lo haya rechazado, y que no haya sido aceptado.
	 * Cumpliendose lo anterior, en caso de haber match, se procede al proceso de confirmación eliminandolo 
	 * de la columnfamily de nuevos matches y agregandolo en la columnfamily de aceptados.
	 * Luego se crea el chat para poder iniciar la conversación entre ambos usuarios.
	 *
	 * @param idUser
	 * @param idUserConfirmed 
	 * @throw EntityNotFoundException
	 * @throw EntityExistsException
	 * @throw IllegalStateException
	 */
	void confirmUser(string idUser, string idUserConfirmed);

	/**
	 * Devuelve false si esta el usuario esta en la lista de si propia, en la de no propia o ajena,
	 * en la de confirmados propia o si ya se creo el chat
	 */
	bool isACandidate(string idUser, string idOtherUser);

};

#endif /* MATCHSERVICE_H_ */
