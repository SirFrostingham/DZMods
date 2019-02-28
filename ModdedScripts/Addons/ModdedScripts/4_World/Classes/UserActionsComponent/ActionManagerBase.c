modded class ActionManagerBase
{
	override void Update(int pCurrentCommandID)
	{
		if(m_CurrentActionData == NULL)
		{
			return;
		}
		if(m_CurrentActionData)
		{
			if(m_Interrupted)
			{
				LocalInterrupt();
				m_Interrupted = false;
			}
			if(m_CurrentActionData.m_State != UA_AM_PENDING && m_CurrentActionData.m_State != UA_AM_REJECTED && m_CurrentActionData.m_State != UA_AM_ACCEPTED)
			{
				m_CurrentActionData.m_Action.OnUpdate(m_CurrentActionData);
			}
		}
	}
	
}