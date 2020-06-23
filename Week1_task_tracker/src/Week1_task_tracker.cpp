#include <iostream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

TaskStatus Next(const TaskStatus status) {
    return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return person_tasks_.at(person);
	}

	void AddNewTask(const string& person) {
		++person_tasks_[person][TaskStatus::NEW];
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		if (person_tasks_.count(person) == 0) {
			TasksInfo temp;
			return tie(temp, temp);
		}
		TasksInfo updated_tasks, not_updated_tasks;
		TasksInfo new_person_tasks = person_tasks_[person];

		for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
			int current_tasks;
			if (person_tasks_[person].count(status) == 0) {
				current_tasks = 0;
			} else 	{
				current_tasks = person_tasks_[person].at(status);
			}

			if (current_tasks != 0) {
				int update_count = min(task_count, current_tasks);

				if (update_count > 0) {
					updated_tasks[Next(status)] = update_count;
					new_person_tasks[status] -= update_count;
					if (new_person_tasks[status] == 0) {
						new_person_tasks.erase(status);
					}
					new_person_tasks[Next(status)] += update_count;
				}

				if (update_count < current_tasks) {
					not_updated_tasks[status] = current_tasks - update_count;
				}
				task_count -= update_count;
			}
		}
		person_tasks_[person] = new_person_tasks;
		return tie(updated_tasks, not_updated_tasks);
	}

private:
	map<string, TasksInfo> person_tasks_;
};

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" << ", "
		 << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" << ", "
		 << tasks_info[TaskStatus::TESTING] << " tasks are being tested" << ", "
		 << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}
