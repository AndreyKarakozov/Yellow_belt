//const int NUM_TASK_STATUS = 4;
//
//TaskStatus operator+(const TaskStatus status, const int add_value) {
//    return static_cast<TaskStatus>((static_cast<int>(status) + add_value) % NUM_TASK_STATUS);
//}
//
//class TeamTasks {
//public:
//	const TasksInfo& GetPersonTasksInfo(const string& person) const {
//		return person_to_tasks.at(person);
//	}
//
//	void AddNewTask(const string& person) {
//		person_to_tasks[person][TaskStatus::NEW]++;
//	}
//
//	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
//		if (person_to_tasks.count(person) == 0) {
//			TasksInfo temp;
//			return tie(temp, temp);
//		}
//		TasksInfo updated_tasks, not_updated_tasks;
//		TasksInfo new_person_tasks = person_to_tasks[person];
//
//		for (const TaskStatus status : {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING}) {
//			int current_tasks;
//			if (person_to_tasks[person].count(status) == 0) {
//				current_tasks = 0;
//			} else 	{
//				current_tasks = person_to_tasks[person].at(status);
//			}
//
//			if (current_tasks != 0) {
//				int update_count = min(task_count, current_tasks);
//
//				if (update_count > 0) {
//					updated_tasks[status + 1] = update_count;
//					new_person_tasks[status] -= update_count;
//					if (new_person_tasks[status] == 0) {
//						new_person_tasks.erase(status);
//					}
//					new_person_tasks[status + 1] += update_count;
//				}
//
//				if (update_count < current_tasks) {
//					not_updated_tasks[status] = current_tasks - update_count;
//				}
//				task_count -= update_count;
//			}
//		}
//		person_to_tasks[person] = new_person_tasks;
//		return tie(updated_tasks, not_updated_tasks);
//	}
//
//private:
//	map<string, TasksInfo> person_to_tasks;
//};
